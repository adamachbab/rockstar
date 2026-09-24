#pragma once

namespace paging {

    constexpr std::uint64_t page_size_4kb = 0x1000ull;
    constexpr std::uint64_t page_size_2mb = 0x200000ull;
    constexpr std::uint64_t page_size_1gb = 0x40000000ull;
    constexpr std::uint64_t page_mask_4kb = 0x0FFFull;
    constexpr std::uint64_t page_mask_2mb = 0x1FFFFFull;
    constexpr std::uint64_t page_mask_1gb = 0x3FFFFFFFull;
    constexpr std::uint32_t page_shift = 12;
    constexpr std::uint32_t max_processors = 64;

    constexpr std::uint64_t cr3_pfn_mask = 0x000FFFFFFFFFF000ull;

    enum class page_protection_t : std::uint32_t {
        no_access = 0,
        read_only = 1,
        read_write = 2,
        read_execute = 3,
        read_write_execute = 4
    };

    union virtual_address_t {
        struct {
            std::uint64_t m_offset : 12;
            std::uint64_t m_pt_index : 9;
            std::uint64_t m_pd_index : 9;
            std::uint64_t m_pdpt_index : 9;
            std::uint64_t m_pml4_index : 9;
            std::uint64_t m_sign_extend : 16;
        } m_bits;
        std::uint64_t m_value;
    };

    enum class walk_result_t : std::uint8_t {
        success = 0,
        not_present = 1,
        huge_page_2mb = 2,
        huge_page_1gb = 3,
        invalid = 4
    };

    struct page_walk_t {
        walk_result_t m_result;
        std::uint64_t m_physical_address;
        nt::pte_t* m_pte;
    };

    __forceinline std::uint64_t virtual_to_physical( std::uint64_t va ) noexcept {
        return kernel::api::mm::get_physical_address( reinterpret_cast< const void* >( va ) );
    }

    __forceinline std::uint64_t physical_to_virtual( std::uint64_t pa ) noexcept {
        return reinterpret_cast< std::uint64_t >( kernel::api::mm::get_virtual_for_physical( pa ) );
    }

    __forceinline bool is_physical_valid( std::uint64_t pa, std::size_t size = 1 ) noexcept {
        if ( !pa || !size ) return false;
        constexpr std::uint64_t max_pa = 1ull << 52;
        if ( pa >= max_pa ) return false;
        if ( size > max_pa - pa ) return false;
        return true;
    }

    __forceinline std::uint64_t get_system_cr3( ) noexcept {
        return kernel::symbols::directory_table_base( );
    }

    __forceinline bool pte_is_sane( std::uint64_t entry ) noexcept {
        if ( ( entry & 1ull ) == 0 ) return true;
        const std::uint64_t pfn = ( entry >> 12 ) & 0x000FFFFFFFFFull;
        return pfn != 0;
    }

    __forceinline page_walk_t walk( std::uint64_t target_cr3, std::uint64_t va ) noexcept {
        page_walk_t out{ walk_result_t::invalid, 0, nullptr };

        if ( !target_cr3 ) return out;

        virtual_address_t addr{ };
        addr.m_value = va;

        const std::uint64_t pml4_pa = target_cr3 & cr3_pfn_mask;
        const std::uint64_t pml4_va = physical_to_virtual( pml4_pa );
        if ( !pml4_va ) return out;

        auto pml4 = reinterpret_cast< volatile nt::pml4e_t* >( pml4_va );
        const auto pml4e_val = pml4[ addr.m_bits.m_pml4_index ].m_flags;
        if ( !pte_is_sane( pml4e_val ) ) return out;
        if ( ( pml4e_val & 1ull ) == 0 ) { out.m_result = walk_result_t::not_present; return out; }

        const std::uint64_t pdpt_pa = ( pml4e_val >> 12 & 0x000FFFFFFFFFull ) << 12;
        const std::uint64_t pdpt_va = physical_to_virtual( pdpt_pa );
        if ( !pdpt_va ) return out;

        auto pdpt = reinterpret_cast< volatile nt::pdpte_t* >( pdpt_va );
        const auto pdpte_val = pdpt[ addr.m_bits.m_pdpt_index ].m_flags;
        if ( !pte_is_sane( pdpte_val ) ) return out;
        if ( ( pdpte_val & 1ull ) == 0 ) { out.m_result = walk_result_t::not_present; return out; }

        if ( pdpte_val & ( 1ull << 7 ) ) {
            out.m_result = walk_result_t::huge_page_1gb;
            const std::uint64_t base = ( pdpte_val >> 12 & 0x000FFFFFFFFFull ) << 12;
            out.m_physical_address = ( base & ~page_mask_1gb ) + ( va & page_mask_1gb );
            return out;
        }

        const std::uint64_t pd_pa = ( pdpte_val >> 12 & 0x000FFFFFFFFFull ) << 12;
        const std::uint64_t pd_va = physical_to_virtual( pd_pa );
        if ( !pd_va ) return out;

        auto pd = reinterpret_cast< volatile nt::pde_t* >( pd_va );
        const auto pde_val = pd[ addr.m_bits.m_pd_index ].m_flags;
        if ( !pte_is_sane( pde_val ) ) return out;
        if ( ( pde_val & 1ull ) == 0 ) { out.m_result = walk_result_t::not_present; return out; }

        if ( pde_val & ( 1ull << 7 ) ) {
            out.m_result = walk_result_t::huge_page_2mb;
            const std::uint64_t base = ( pde_val >> 12 & 0x000FFFFFFFFFull ) << 12;
            out.m_physical_address = ( base & ~page_mask_2mb ) + ( va & page_mask_2mb );
            return out;
        }

        const std::uint64_t pt_pa = ( pde_val >> 12 & 0x000FFFFFFFFFull ) << 12;
        const std::uint64_t pt_va = physical_to_virtual( pt_pa );
        if ( !pt_va ) return out;

        auto pt = reinterpret_cast< nt::pte_t* >( pt_va );
        auto& pte = pt[ addr.m_bits.m_pt_index ];
        if ( ( pte.m_flags & 1ull ) == 0 ) { out.m_result = walk_result_t::not_present; return out; }

        const std::uint64_t base = pte.m_hard.m_pfn << 12;
        out.m_result = walk_result_t::success;
        out.m_physical_address = base + ( va & page_mask_4kb );
        out.m_pte = &pte;
        return out;
    }

    __forceinline nt::pte_t* walk_to_pte( std::uint64_t target_cr3, std::uint64_t va ) noexcept {
        auto r = walk( target_cr3, va );
        return r.m_result == walk_result_t::success ? r.m_pte : nullptr;
    }

    __forceinline std::uint64_t walk_to_physical( std::uint64_t target_cr3, std::uint64_t va ) noexcept {
        auto r = walk( target_cr3, va );
        switch ( r.m_result ) {
        case walk_result_t::success:
        case walk_result_t::huge_page_2mb:
        case walk_result_t::huge_page_1gb:
            return r.m_physical_address;
        default:
            return 0;
        }
    }

} // namespace paging