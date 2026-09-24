#pragma once

namespace kernel::api::ki {

    __forceinline std::uint64_t system_call64( ) noexcept {
        return symbols::get( ).m_ki.m_system_call64;
    }

    __forceinline std::uint64_t system_call64_shadow( ) noexcept {
        return symbols::get( ).m_ki.m_system_call64_shadow;
    }

    __forceinline void* nmi_callback_list_head( ) noexcept {
        const auto addr = symbols::get( ).m_ki.m_nmi_callback_list_head;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline void* service_table( ) noexcept {
        const auto addr = symbols::get( ).m_ki.m_service_table;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline std::uint32_t service_limit( ) noexcept {
        const auto addr = symbols::get( ).m_ki.m_service_limit;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint32_t* >( addr );
    }

    __forceinline void get_gdt_idt( void* buffer ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ki.m_get_gdt_idt, buffer );
    }

    __forceinline std::uint64_t page_fault( ) noexcept {
        return symbols::get( ).m_ki.m_page_fault;
    }

} // namespace kernel::api::ki