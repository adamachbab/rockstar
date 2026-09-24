#pragma once

namespace paging::pte_remap {

    struct core_mapping_t {
        std::uint64_t m_virtual_address;
        nt::pte_t* m_pte_address;
        std::uint64_t m_original_pte;
    };

    extern core_mapping_t m_core_mappings[ paging::max_processors ];
    extern bool           m_is_initialized;

    bool          initialize( ) noexcept;
    void          cleanup( ) noexcept;

    bool          read_physical( std::uint64_t pa, void* buffer, std::size_t size ) noexcept;
    bool          write_physical( std::uint64_t pa, const void* buffer, std::size_t size ) noexcept;
    bool          read_virtual( std::uint64_t target_cr3, std::uint64_t va, void* buffer, std::size_t size ) noexcept;
    bool          write_virtual( std::uint64_t target_cr3, std::uint64_t va, const void* buffer, std::size_t size ) noexcept;

} // namespace paging::pte_remap