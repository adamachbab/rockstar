#pragma once

namespace kernel::api::misc {

    __forceinline void* hal_private_dispatch_table( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_hal_private_dispatch_table;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline std::uint64_t etw_trace_silo_kernel_event( ) noexcept {
        return symbols::get( ).m_misc.m_etw_trace_silo_kernel_event;
    }

    __forceinline void* po_idle( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_po_idle;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline std::uint32_t ci_options( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_ci_options;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint32_t* >( addr );
    }

    __forceinline std::uint8_t* pool_big_page_table( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_pool_big_page_table;
        if ( !addr ) return nullptr;
        return *reinterpret_cast< std::uint8_t** >( addr );
    }

    __forceinline std::uint64_t pool_big_page_table_size( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_pool_big_page_table_size;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint64_t* >( addr );
    }

    __forceinline nt::rtl_avl_table_t* piddb_cache_table( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_piddb_cache_table;
        return addr ? reinterpret_cast< nt::rtl_avl_table_t* >( addr ) : nullptr;
    }

    __forceinline void* piddb_lock( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_piddb_lock;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline std::uint64_t expected_ci_g_pfn( ) noexcept {
        const auto addr = symbols::get( ).m_misc.m_expected_ci_g_pfn;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint64_t* >( addr );
    }

} // namespace kernel::api::misc