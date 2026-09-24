#include <includes.hpp>

bool entry( kernel::symbols::entry_t* entry ) {
    if ( !entry || !kernel::symbols::initialize( entry ) )
        return false;

    core::log::info( "entry", "image_base = 0x%llx\n", entry->m_image_base );
    core::log::info( "entry", "image_size = 0x%llx\n", entry->m_image_size );
    core::log::info( "entry", "ntoskrnl_base = 0x%llx\n", entry->m_ntoskrnl_base );
    core::log::info( "entry", "dtb = 0x%llx\n", entry->m_directory_table_base );
    core::log::info( "entry", "rdata @ 0x%llx (0x%llx bytes)\n", entry->m_rdata_offset, entry->m_rdata_size );
    core::log::info( "entry", "data @ 0x%llx (0x%llx bytes)\n", entry->m_data_offset,  entry->m_data_size );

    if ( !paging::pte_remap::initialize( ) ) {
        core::log::error( "entry", "pte_remap init failed\n" );
        return false;
    }

    if ( !paging::shadow_pt::initialize( ) ) {
        core::log::error( "entry", "shadow_pt init failed\n" );
        paging::pte_remap::cleanup( );
        return false;
    }
    
    core::log::info( "entry", "success\n" );
    return true;
}