#include <includes.hpp>

namespace paging::pte_remap {

    core_mapping_t m_core_mappings[ paging::max_processors ] = { };
    bool           m_is_initialized = false;

    namespace detail {

        struct dispatch_guard_t {
            std::uint8_t m_old_irql;

            __forceinline dispatch_guard_t( ) noexcept {
                m_old_irql = kernel::api::ke::raise_irql_to_dpc( );
            }
            __forceinline ~dispatch_guard_t( ) noexcept {
                kernel::api::ke::lower_irql( m_old_irql );
            }

            dispatch_guard_t( const dispatch_guard_t& ) = delete;
            dispatch_guard_t& operator=( const dispatch_guard_t& ) = delete;
        };

        __forceinline std::uint32_t current_core( ) noexcept {
            const auto idx = kernel::api::ke::get_current_processor_number( );
            return idx < paging::max_processors ? idx : 0;
        }

        __forceinline void tlb_flush_local( std::uint64_t va ) noexcept {
            intrin::invalidate_page( reinterpret_cast< void* >( va ) );
        }

        __forceinline void write_pte_atomic( nt::pte_t* pte, std::uint64_t value ) noexcept {
            *reinterpret_cast< volatile std::uint64_t* >( pte ) = value;
            intrin::mem_fence( );
        }

    } // namespace detail

    bool initialize( ) noexcept {
        if ( m_is_initialized )
            return false;

        const auto system_cr3 = paging::get_system_cr3( );
        if ( !system_cr3 ) {
            core::log::error( "pte_remap", "no system cr3\n" );
            return false;
        }

        const std::uint32_t active = kernel::api::ke::query_active_processor_count_ex( 0xFFFF );
        const std::uint32_t cores = active < paging::max_processors ? active : paging::max_processors;

        for ( std::uint32_t i = 0; i < cores; ++i ) {
            auto page = kernel::api::mm::allocate_independent_pages( paging::page_size_4kb );
            if ( !page ) {
                core::log::error( "pte_remap", "alloc failed core=%u\n", i );
                cleanup( );
                return false;
            }

            std::mem_zero( page, paging::page_size_4kb );

            const auto va = reinterpret_cast< std::uint64_t >( page );
            const auto pte = paging::walk_to_pte( system_cr3, va );
            if ( !pte ) {
                core::log::error( "pte_remap", "walk failed core=%u\n", i );
                kernel::api::mm::free_independent_pages( page, paging::page_size_4kb );
                cleanup( );
                return false;
            }

            m_core_mappings[ i ].m_virtual_address = va;
            m_core_mappings[ i ].m_pte_address = pte;
            m_core_mappings[ i ].m_original_pte = pte->m_flags;
        }

        m_is_initialized = true;
        core::log::info( "pte_remap", "initialized %u cores\n", cores );
        return true;
    }

    void cleanup( ) noexcept {
        for ( std::uint32_t i = 0; i < paging::max_processors; ++i ) {
            auto& m = m_core_mappings[ i ];

            if ( m.m_pte_address && m.m_virtual_address ) {
                detail::dispatch_guard_t g;
                detail::write_pte_atomic( m.m_pte_address, m.m_original_pte );
                detail::tlb_flush_local( m.m_virtual_address );
            }

            if ( m.m_virtual_address ) {
                kernel::api::mm::free_independent_pages(
                    reinterpret_cast< void* >( m.m_virtual_address ),
                    paging::page_size_4kb );
            }
        }

        std::mem_zero( m_core_mappings, sizeof( m_core_mappings ) );
        m_is_initialized = false;
    }

    namespace detail {

        __forceinline bool remap_and_access( core_mapping_t& m,
            std::uint64_t page_base_pa,
            std::size_t   page_offset,
            void* user_buf,
            std::size_t   chunk,
            bool          write ) noexcept {

            std::uint64_t new_pte = m.m_original_pte;
            new_pte &= ~( 0x000FFFFFFFFFF000ull );
            new_pte |= ( page_base_pa & 0x000FFFFFFFFFF000ull );
            new_pte |= 0x3ull;
            new_pte &= ~( 1ull << 63 );

            write_pte_atomic( m.m_pte_address, new_pte );
            tlb_flush_local( m.m_virtual_address );

            auto mapped = reinterpret_cast< std::uint8_t* >( m.m_virtual_address + page_offset );
            if ( write ) std::mem_copy( mapped, user_buf, chunk );
            else         std::mem_copy( user_buf, mapped, chunk );

            write_pte_atomic( m.m_pte_address, m.m_original_pte );
            tlb_flush_local( m.m_virtual_address );
            return true;
        }

        __forceinline bool transfer_physical( std::uint64_t pa,
            void* buffer, std::size_t size, bool write ) noexcept {
            if ( !m_is_initialized || !buffer || !size )
                return false;

            dispatch_guard_t g;

            const auto core = current_core( );
            auto& m = m_core_mappings[ core ];
            if ( !m.m_pte_address || !m.m_virtual_address )
                return false;

            auto remaining = size;
            auto current_pa = pa;
            auto ptr = static_cast< std::uint8_t* >( buffer );

            while ( remaining > 0 ) {
                if ( !paging::is_physical_valid( current_pa, 1 ) )
                    return false;

                const auto page_offset = current_pa & paging::page_mask_4kb;
                const auto page_base = current_pa & ~paging::page_mask_4kb;
                const auto chunk = std::min_of<std::size_t>( remaining,
                    paging::page_size_4kb - page_offset );

                if ( !remap_and_access( m, page_base, page_offset, ptr, chunk, write ) )
                    return false;

                current_pa += chunk;
                ptr += chunk;
                remaining -= chunk;
            }
            return true;
        }

        __forceinline bool transfer_virtual( std::uint64_t target_cr3, std::uint64_t va,
            void* buffer, std::size_t size, bool write ) noexcept {
            if ( !target_cr3 || !va || !buffer || !size )
                return false;

            auto remaining = size;
            auto current_va = va;
            auto ptr = static_cast< std::uint8_t* >( buffer );

            while ( remaining > 0 ) {
                const auto r = paging::walk( target_cr3, current_va );

                std::uint64_t phys = 0;
                std::size_t   page_offset = 0;
                std::size_t   page_avail = 0;

                switch ( r.m_result ) {
                case paging::walk_result_t::success:
                    page_offset = current_va & paging::page_mask_4kb;
                    phys = r.m_physical_address;
                    page_avail = paging::page_size_4kb - page_offset;
                    break;
                case paging::walk_result_t::huge_page_2mb:
                    page_offset = current_va & paging::page_mask_2mb;
                    phys = r.m_physical_address;
                    page_avail = paging::page_size_2mb - page_offset;
                    break;
                case paging::walk_result_t::huge_page_1gb:
                    page_offset = current_va & paging::page_mask_1gb;
                    phys = r.m_physical_address;
                    page_avail = paging::page_size_1gb - page_offset;
                    break;
                default:
                    return false;
                }

                const auto chunk = std::min_of<std::size_t>( remaining, page_avail );
                if ( !transfer_physical( phys, ptr, chunk, write ) )
                    return false;

                current_va += chunk;
                ptr += chunk;
                remaining -= chunk;
            }
            return true;
        }

    } // namespace detail

    bool read_physical( std::uint64_t pa, void* buffer, std::size_t size ) noexcept {
        return detail::transfer_physical( pa, buffer, size, false );
    }

    bool write_physical( std::uint64_t pa, const void* buffer, std::size_t size ) noexcept {
        return detail::transfer_physical( pa, const_cast< void* >( buffer ), size, true );
    }

    bool read_virtual( std::uint64_t target_cr3, std::uint64_t va,
        void* buffer, std::size_t size ) noexcept {
        return detail::transfer_virtual( target_cr3, va, buffer, size, false );
    }

    bool write_virtual( std::uint64_t target_cr3, std::uint64_t va,
        const void* buffer, std::size_t size ) noexcept {
        return detail::transfer_virtual( target_cr3, va, const_cast< void* >( buffer ), size, true );
    }

} // namespace paging::pte_remap