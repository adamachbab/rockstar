#pragma once

namespace kernel::api::rtl {

    __forceinline void init_unicode_string( nt::unicode_string_t* dest,
        const std::wchar_alias* src ) noexcept {
        using fn_t = void( nt::unicode_string_t*, const std::wchar_alias* );
        symbols::call< fn_t >( symbols::get( ).m_rtl.m_init_unicode_string, dest, src );
    }

    __forceinline void init_ansi_string( nt::ansi_string_t* dest, const char* src ) noexcept {
        using fn_t = void( nt::ansi_string_t*, const char* );
        symbols::call< fn_t >( symbols::get( ).m_rtl.m_init_ansi_string, dest, src );
    }

    __forceinline std::int32_t compare_unicode_string( nt::unicode_string_t* a,
        nt::unicode_string_t* b, bool case_insensitive ) noexcept {
        using fn_t = std::int32_t( nt::unicode_string_t*, nt::unicode_string_t*, bool );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_compare_unicode_string,
            a, b, case_insensitive );
    }

    __forceinline bool equal_unicode_string( nt::unicode_string_t* a,
        nt::unicode_string_t* b, bool case_insensitive ) noexcept {
        using fn_t = bool( nt::unicode_string_t*, nt::unicode_string_t*, bool );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_equal_unicode_string,
            a, b, case_insensitive );
    }

    __forceinline std::int32_t copy_unicode_string( nt::unicode_string_t* dest,
        nt::unicode_string_t* src ) noexcept {
        using fn_t = std::int32_t( nt::unicode_string_t*, nt::unicode_string_t* );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_copy_unicode_string, dest, src );
    }

    __forceinline void free_unicode_string( nt::unicode_string_t* str ) noexcept {
        using fn_t = void( nt::unicode_string_t* );
        symbols::call< fn_t >( symbols::get( ).m_rtl.m_free_unicode_string, str );
    }

    __forceinline std::int32_t unicode_string_to_ansi_string( nt::ansi_string_t* dest,
        nt::unicode_string_t* src, std::uint8_t allocate_dest ) noexcept {
        using fn_t = std::int32_t( nt::ansi_string_t*, nt::unicode_string_t*, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_unicode_string_to_ansi_string,
            dest, src, allocate_dest );
    }

    __forceinline std::int32_t ansi_string_to_unicode_string( nt::unicode_string_t* dest,
        nt::ansi_string_t* src, std::uint8_t allocate_dest ) noexcept {
        using fn_t = std::int32_t( nt::unicode_string_t*, nt::ansi_string_t*, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_ansi_string_to_unicode_string,
            dest, src, allocate_dest );
    }

    __forceinline std::int32_t create_user_thread( void* process, void* security_descriptor,
        std::uint8_t create_suspended, std::uint64_t stack_zero_bits,
        std::size_t* stack_reserved, std::size_t* stack_commit, void* start_address,
        void* start_parameter, void** thread_handle, nt::client_id_t* client_id ) noexcept {
        using fn_t = std::int32_t( void*, void*, std::uint8_t, std::uint64_t, std::size_t*,
            std::size_t*, void*, void*, void**, nt::client_id_t* );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_create_user_thread,
            process, security_descriptor, create_suspended, stack_zero_bits,
            stack_reserved, stack_commit, start_address, start_parameter,
            thread_handle, client_id );
    }

    __forceinline std::int32_t get_version( nt::rtl_osversioninfo_ex_w_t* info ) noexcept {
        using fn_t = std::int32_t( nt::rtl_osversioninfo_ex_w_t* );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_get_version, info );
    }

    __forceinline void* lookup_element_generic_table_avl( nt::rtl_avl_table_t* table,
        void* buffer ) noexcept {
        using fn_t = void* ( nt::rtl_avl_table_t*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_lookup_element_generic_table_avl,
            table, buffer );
    }

    __forceinline bool delete_element_generic_table_avl( nt::rtl_avl_table_t* table,
        void* buffer ) noexcept {
        using fn_t = bool( nt::rtl_avl_table_t*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_delete_element_generic_table_avl,
            table, buffer );
    }

    __forceinline void* insert_element_generic_table_avl( nt::rtl_avl_table_t* table,
        void* buffer, std::uint32_t buffer_size, std::uint8_t* new_element ) noexcept {
        using fn_t = void* ( nt::rtl_avl_table_t*, void*, std::uint32_t, std::uint8_t* );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_insert_element_generic_table_avl,
            table, buffer, buffer_size, new_element );
    }

    __forceinline void* enumerate_generic_table_avl( nt::rtl_avl_table_t* table,
        std::uint8_t restart ) noexcept {
        using fn_t = void* ( nt::rtl_avl_table_t*, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_enumerate_generic_table_avl,
            table, restart );
    }

    __forceinline void* get_element_generic_table_avl( nt::rtl_avl_table_t* table,
        std::uint32_t index ) noexcept {
        using fn_t = void* ( nt::rtl_avl_table_t*, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_get_element_generic_table_avl,
            table, index );
    }

    __forceinline std::uint32_t number_generic_table_elements_avl( nt::rtl_avl_table_t* table ) noexcept {
        using fn_t = std::uint32_t( nt::rtl_avl_table_t* );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_number_generic_table_elements_avl, table );
    }

    __forceinline nt::list_entry_t* debug_print_callback_list( ) noexcept {
        const auto addr = symbols::get( ).m_rtl.m_debug_print_callback_list;
        return addr ? reinterpret_cast< nt::list_entry_t* >( addr ) : nullptr;
    }

    __forceinline void* pc_to_file_header( void* pc_value, void** base_of_image ) noexcept {
        using fn_t = void* ( void*, void** );
        return symbols::call< fn_t >( symbols::get( ).m_rtl.m_pc_to_file_header,
            pc_value, base_of_image );
    }

} // namespace kernel::api::rtl

namespace kernel::api::crt {

    __forceinline void* memcpy( void* dst, const void* src, std::size_t n ) noexcept {
        using fn_t = void* ( void*, const void*, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_memcpy, dst, src, n );
    }

    __forceinline void* memset( void* dst, int value, std::size_t n ) noexcept {
        using fn_t = void* ( void*, int, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_memset, dst, value, n );
    }

    __forceinline void* memmove( void* dst, const void* src, std::size_t n ) noexcept {
        using fn_t = void* ( void*, const void*, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_memmove, dst, src, n );
    }

    __forceinline int memcmp( const void* a, const void* b, std::size_t n ) noexcept {
        using fn_t = int( const void*, const void*, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_memcmp, a, b, n );
    }

    __forceinline int strcmp( const char* a, const char* b ) noexcept {
        using fn_t = int( const char*, const char* );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_strcmp, a, b );
    }

    __forceinline int strncmp( const char* a, const char* b, std::size_t n ) noexcept {
        using fn_t = int( const char*, const char*, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_strncmp, a, b, n );
    }

    __forceinline std::size_t strlen( const char* s ) noexcept {
        using fn_t = std::size_t( const char* );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_strlen, s );
    }

    __forceinline char* strcpy( char* dst, const char* src ) noexcept {
        using fn_t = char* ( char*, const char* );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_strcpy, dst, src );
    }

    __forceinline char* strncpy( char* dst, const char* src, std::size_t n ) noexcept {
        using fn_t = char* ( char*, const char*, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_strncpy, dst, src, n );
    }

    __forceinline std::size_t wcslen( const std::wchar_alias* s ) noexcept {
        using fn_t = std::size_t( const std::wchar_alias* );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_wcslen, s );
    }

    __forceinline int wcscmp( const std::wchar_alias* a, const std::wchar_alias* b ) noexcept {
        using fn_t = int( const std::wchar_alias*, const std::wchar_alias* );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_wcscmp, a, b );
    }

    __forceinline std::wchar_alias* wcscpy( std::wchar_alias* dst, const std::wchar_alias* src ) noexcept {
        using fn_t = std::wchar_alias* ( std::wchar_alias*, const std::wchar_alias* );
        return symbols::call< fn_t >( symbols::get( ).m_crt.m_wcscpy, dst, src );
    }

} // namespace kernel::api::crt