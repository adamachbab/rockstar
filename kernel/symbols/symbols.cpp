#include <includes.hpp>

namespace kernel::symbols {

    symbols_t     m_symbols = { };
    std::uint64_t m_image_base = 0;
    std::uint64_t m_image_size = 0;
    std::uint64_t m_ntoskrnl_base = 0;
    std::uint64_t m_directory_table_base = 0;

    bool initialize( const entry_t* entry ) noexcept {
        if ( !entry || !entry->is_valid( ) )
            return false;

        std::mem_copy( &m_symbols, &entry->m_pdb, sizeof( symbols_t ) );

        m_image_base = entry->m_image_base;
        m_image_size = entry->m_image_size;
        m_ntoskrnl_base = entry->m_ntoskrnl_base;
        m_directory_table_base = entry->m_directory_table_base;

        return m_symbols.is_valid( );
    }

    const symbols_t& get( ) noexcept { return m_symbols; }
    std::uint64_t    image_base( ) noexcept { return m_image_base; }
    std::uint64_t    image_size( ) noexcept { return m_image_size; }
    std::uint64_t    ntoskrnl_base( ) noexcept { return m_ntoskrnl_base; }
    std::uint64_t    directory_table_base( ) noexcept { return m_directory_table_base; }

} // namespace kernel::symbols