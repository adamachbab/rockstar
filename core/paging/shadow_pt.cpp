#include <includes.hpp>

namespace paging::shadow_pt {

    shadow_hierarchy_t m_hierarchy = { };
    index_cursor_t     m_cursor = { };
    volatile long      m_spinlock = 0;
    bool               m_is_initialized = false;

    namespace detail {

        struct lock_guard_t {
            std::uint8_t m_old_irql;

            __forceinline lock_guard_t( ) noexcept {
                m_old_irql = kernel::api::ke::raise_irql_to_dpc( );
                while ( intrin::interlocked_compare_exchange( &m_spinlock, 1, 0 ) != 0 )
                    intrin::cpu_pause( );
            }

            __forceinline ~lock_guard_t( ) noexcept {
                intrin::mem_fence( );
                intrin::interlocked_exchange( &m_spinlock, 0 );
                kernel::api::ke::lower_irql( m_old_irql );
            }

            lock_guard_t( const lock_guard_t& ) = delete;
            lock_guard_t& operator=( const lock_guard_t& ) = delete;
        };

        __forceinline void write_entry_atomic( volatile std::uint64_t* dst, std::uint64_t val ) noexcept {
            *dst = val;
            intrin::mem_fence( );
        }

        __forceinline void invalidate_all_cpus( std::uint64_t va ) noexcept {
            kernel::api::ke::flush_single_tb( va, true, true );
        }

        __forceinline bool find_free_pml4_slot( std::uint64_t system_cr3,
            std::uint16_t& out_index ) noexcept {
            const auto pml4_va = paging::physical_to_virtual( system_cr3 & paging::cr3_pfn_mask );
            if ( !pml4_va ) return false;

            auto pml4 = reinterpret_cast< volatile nt::pml4e_t* >( pml4_va );
            for ( std::uint16_t i = 256; i < 510; ++i ) {
                if ( ( pml4[ i ].m_flags & 1ull ) == 0 ) {
                    out_index = i;
                    return true;
                }
            }
            return false;
        }

        __forceinline void write_pml4_entry( std::uint64_t system_cr3,
            std::uint16_t index, std::uint64_t pfn ) noexcept {
            const auto pa = ( system_cr3 & paging::cr3_pfn_mask ) + ( index * sizeof( nt::pml4e_t ) );
            const auto va = paging::physical_to_virtual( pa );
            if ( !va ) return;

            std::uint64_t entry = 0;
            entry |= 1ull;
            entry |= 1ull << 1;
            entry |= ( pfn & 0x000FFFFFFFFFull ) << 12;

            write_entry_atomic( reinterpret_cast< volatile std::uint64_t* >( va ), entry );
        }

        __forceinline void clear_pml4_entry( std::uint64_t system_cr3, std::uint16_t index ) noexcept {
            const auto pa = ( system_cr3 & paging::cr3_pfn_mask ) + ( index * sizeof( nt::pml4e_t ) );
            const auto va = paging::physical_to_virtual( pa );
            if ( !va ) return;
            write_entry_atomic( reinterpret_cast< volatile std::uint64_t* >( va ), 0ull );
        }

        __forceinline bool allocate_shadow_page( std::uint64_t& out_va, std::uint64_t& out_pfn ) noexcept {
            auto page = kernel::api::mm::allocate_independent_pages( paging::page_size_4kb );
            if ( !page ) return false;

            std::mem_zero( page, paging::page_size_4kb );

            const auto va = reinterpret_cast< std::uint64_t >( page );
            const auto pa = paging::virtual_to_physical( va );
            if ( !pa ) {
                kernel::api::mm::free_independent_pages( page, paging::page_size_4kb );
                return false;
            }

            out_va = va;
            out_pfn = pa >> paging::page_shift;
            return true;
        }

        __forceinline void free_shadow_page( std::uint64_t va ) noexcept {
            if ( va ) {
                kernel::api::mm::free_independent_pages(
                    reinterpret_cast< void* >( va ),
                    paging::page_size_4kb );
            }
        }

        __forceinline bool advance_cursor( index_cursor_t& cursor ) noexcept {
            if ( cursor.m_pt_index == 0xFFFF ) {
                cursor.m_pt_index = 0;
                return true;
            }
            if ( cursor.m_pt_index >= 511 ) return false;
            ++cursor.m_pt_index;
            return true;
        }

        __forceinline std::uint64_t build_pte( std::uint64_t pfn,
            paging::page_protection_t p, bool user ) noexcept {

            std::uint64_t e = 0;
            e |= ( pfn & 0x000FFFFFFFFFull ) << 12;

            if ( p == paging::page_protection_t::no_access )
                return 0;

            e |= 1ull;
            if ( user ) e |= 1ull << 2;

            switch ( p ) {
            case paging::page_protection_t::read_only:
                e |= 1ull << 63;
                break;
            case paging::page_protection_t::read_write:
                e |= 1ull << 1;
                e |= 1ull << 63;
                break;
            case paging::page_protection_t::read_execute:
                break;
            case paging::page_protection_t::read_write_execute:
                e |= 1ull << 1;
                break;
            default:
                break;
            }
            return e;
        }

        __forceinline paging::virtual_address_t cursor_to_va( const index_cursor_t& cursor,
            std::uint64_t offset ) noexcept {
            paging::virtual_address_t addr{ };
            addr.m_bits.m_pml4_index = cursor.m_pml4_index;
            addr.m_bits.m_pdpt_index = cursor.m_pdpt_index;
            addr.m_bits.m_pd_index = cursor.m_pd_index;
            addr.m_bits.m_pt_index = cursor.m_pt_index;
            addr.m_bits.m_offset = offset;
            addr.m_bits.m_sign_extend = ( cursor.m_pml4_index >= 256 ) ? 0xFFFF : 0;
            return addr;
        }

    } // namespace detail

    bool initialize( ) noexcept {
        if ( m_is_initialized ) return false;

        const auto system_cr3 = paging::get_system_cr3( );
        if ( !system_cr3 ) {
            core::log::error( "shadow_pt", "no system cr3\n" );
            return false;
        }

        std::uint16_t pml4_slot = 0;
        if ( !detail::find_free_pml4_slot( system_cr3, pml4_slot ) ) {
            core::log::error( "shadow_pt", "no free PML4 slot\n" );
            return false;
        }

        if ( !detail::allocate_shadow_page( m_hierarchy.m_pdpt_va, m_hierarchy.m_pdpt_pfn ) ) {
            core::log::error( "shadow_pt", "pdpt alloc failed\n" );
            return false;
        }
        if ( !detail::allocate_shadow_page( m_hierarchy.m_pd_va, m_hierarchy.m_pd_pfn ) ) {
            detail::free_shadow_page( m_hierarchy.m_pdpt_va );
            std::mem_zero( &m_hierarchy, sizeof( m_hierarchy ) );
            core::log::error( "shadow_pt", "pd alloc failed\n" );
            return false;
        }
        if ( !detail::allocate_shadow_page( m_hierarchy.m_pt_va, m_hierarchy.m_pt_pfn ) ) {
            detail::free_shadow_page( m_hierarchy.m_pdpt_va );
            detail::free_shadow_page( m_hierarchy.m_pd_va );
            std::mem_zero( &m_hierarchy, sizeof( m_hierarchy ) );
            core::log::error( "shadow_pt", "pt alloc failed\n" );
            return false;
        }

        {
            auto pdpt = reinterpret_cast< volatile std::uint64_t* >( m_hierarchy.m_pdpt_va );
            std::uint64_t e_pdpt = 0;
            e_pdpt |= 1ull;
            e_pdpt |= 1ull << 1;
            e_pdpt |= ( m_hierarchy.m_pd_pfn & 0x000FFFFFFFFFull ) << 12;
            detail::write_entry_atomic( &pdpt[ 0 ], e_pdpt );

            auto pd = reinterpret_cast< volatile std::uint64_t* >( m_hierarchy.m_pd_va );
            std::uint64_t e_pd = 0;
            e_pd |= 1ull;
            e_pd |= 1ull << 1;
            e_pd |= ( m_hierarchy.m_pt_pfn & 0x000FFFFFFFFFull ) << 12;
            detail::write_entry_atomic( &pd[ 0 ], e_pd );
        }

        detail::write_pml4_entry( system_cr3, pml4_slot, m_hierarchy.m_pdpt_pfn );

        m_cursor = { pml4_slot, 0, 0, 0xFFFF };
        m_spinlock = 0;
        m_is_initialized = true;

        core::log::info( "shadow_pt", "init pml4_slot=%u\n", pml4_slot );
        return true;
    }

    void cleanup( ) noexcept {
        if ( !m_is_initialized ) return;

        {
            detail::lock_guard_t g;
            detail::clear_pml4_entry( paging::get_system_cr3( ), m_cursor.m_pml4_index );
            kernel::api::ke::flush_entire_tb( true, true );
        }

        detail::free_shadow_page( m_hierarchy.m_pt_va );
        detail::free_shadow_page( m_hierarchy.m_pd_va );
        detail::free_shadow_page( m_hierarchy.m_pdpt_va );

        std::mem_zero( &m_hierarchy, sizeof( m_hierarchy ) );
        std::mem_zero( &m_cursor, sizeof( m_cursor ) );

        m_is_initialized = false;
    }

    void* map_physical_page( std::uint64_t pa,
        paging::page_protection_t protection, bool user_accessible ) noexcept {

        if ( !m_is_initialized || !paging::is_physical_valid( pa, paging::page_size_4kb ) )
            return nullptr;

        detail::lock_guard_t g;

        if ( !detail::advance_cursor( m_cursor ) )
            return nullptr;

        const auto page_offset = pa & paging::page_mask_4kb;
        const auto page_base_pfn = pa >> paging::page_shift;

        auto pt = reinterpret_cast< volatile std::uint64_t* >( m_hierarchy.m_pt_va );
        const auto new_pte = detail::build_pte( page_base_pfn, protection, user_accessible );

        detail::write_entry_atomic( &pt[ m_cursor.m_pt_index ], new_pte );

        const auto addr = detail::cursor_to_va( m_cursor, page_offset );
        detail::invalidate_all_cpus( addr.m_value );

        return reinterpret_cast< void* >( addr.m_value );
    }

    bool unmap_last( ) noexcept {
        if ( !m_is_initialized ) return false;

        detail::lock_guard_t g;

        if ( m_cursor.m_pt_index == 0xFFFF ) return false;

        auto pt = reinterpret_cast< volatile std::uint64_t* >( m_hierarchy.m_pt_va );
        detail::write_entry_atomic( &pt[ m_cursor.m_pt_index ], 0ull );

        const auto addr = detail::cursor_to_va( m_cursor, 0 );
        detail::invalidate_all_cpus( addr.m_value );

        if ( m_cursor.m_pt_index > 0 ) --m_cursor.m_pt_index;
        else                            m_cursor.m_pt_index = 0xFFFF;
        return true;
    }

} // namespace paging::shadow_pt