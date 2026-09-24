#pragma once

namespace paging::shadow_pt {

    struct shadow_hierarchy_t {
        std::uint64_t m_pdpt_va;
        std::uint64_t m_pd_va;
        std::uint64_t m_pt_va;
        std::uint64_t m_pdpt_pfn;
        std::uint64_t m_pd_pfn;
        std::uint64_t m_pt_pfn;
    };

    struct index_cursor_t {
        std::uint16_t m_pml4_index;
        std::uint16_t m_pdpt_index;
        std::uint16_t m_pd_index;
        std::uint16_t m_pt_index;
    };

    extern shadow_hierarchy_t m_hierarchy;
    extern index_cursor_t     m_cursor;
    extern volatile long      m_spinlock;
    extern bool               m_is_initialized;

    bool  initialize( ) noexcept;
    void  cleanup( ) noexcept;

    void* map_physical_page( std::uint64_t physical_address,
        paging::page_protection_t protection = paging::page_protection_t::read_write,
        bool user_accessible = false ) noexcept;

    bool  unmap_last( ) noexcept;

} // namespace paging::shadow_pt