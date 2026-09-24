#pragma once

namespace kernel::api::zw {

    __forceinline std::int32_t query_system_information( std::uint32_t info_class,
        void* buffer, std::uint32_t buffer_size, std::uint32_t* return_length ) noexcept {
        using fn_t = std::int32_t( std::uint32_t, void*, std::uint32_t, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_query_system_information,
            info_class, buffer, buffer_size, return_length );
    }

    __forceinline std::int32_t close( void* handle ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_close, handle );
    }

    __forceinline std::int32_t create_file( void** file_handle, std::uint32_t desired_access,
        nt::object_attributes_t* object_attributes, nt::io_status_block_t* io_status_block,
        nt::large_integer_t* allocation_size, std::uint32_t file_attributes,
        std::uint32_t share_access, std::uint32_t create_disposition,
        std::uint32_t create_options, void* ea_buffer, std::uint32_t ea_length ) noexcept {
        using fn_t = std::int32_t( void**, std::uint32_t, nt::object_attributes_t*,
            nt::io_status_block_t*, nt::large_integer_t*, std::uint32_t, std::uint32_t,
            std::uint32_t, std::uint32_t, void*, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_create_file,
            file_handle, desired_access, object_attributes, io_status_block,
            allocation_size, file_attributes, share_access, create_disposition,
            create_options, ea_buffer, ea_length );
    }

    __forceinline std::int32_t read_file( void* file_handle, void* event,
        void* apc_routine, void* apc_context, nt::io_status_block_t* io_status_block,
        void* buffer, std::uint32_t length, nt::large_integer_t* byte_offset,
        std::uint32_t* key ) noexcept {
        using fn_t = std::int32_t( void*, void*, void*, void*, nt::io_status_block_t*,
            void*, std::uint32_t, nt::large_integer_t*, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_read_file,
            file_handle, event, apc_routine, apc_context, io_status_block,
            buffer, length, byte_offset, key );
    }

    __forceinline std::int32_t write_file( void* file_handle, void* event,
        void* apc_routine, void* apc_context, nt::io_status_block_t* io_status_block,
        void* buffer, std::uint32_t length, nt::large_integer_t* byte_offset,
        std::uint32_t* key ) noexcept {
        using fn_t = std::int32_t( void*, void*, void*, void*, nt::io_status_block_t*,
            void*, std::uint32_t, nt::large_integer_t*, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_write_file,
            file_handle, event, apc_routine, apc_context, io_status_block,
            buffer, length, byte_offset, key );
    }

    __forceinline std::int32_t open_key( void** key_handle, std::uint32_t desired_access,
        nt::object_attributes_t* object_attributes ) noexcept {
        using fn_t = std::int32_t( void**, std::uint32_t, nt::object_attributes_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_open_key,
            key_handle, desired_access, object_attributes );
    }

    __forceinline std::int32_t create_key( void** key_handle, std::uint32_t desired_access,
        nt::object_attributes_t* object_attributes, std::uint32_t title_index,
        nt::unicode_string_t* class_name, std::uint32_t create_options,
        std::uint32_t* disposition ) noexcept {
        using fn_t = std::int32_t( void**, std::uint32_t, nt::object_attributes_t*,
            std::uint32_t, nt::unicode_string_t*, std::uint32_t, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_create_key,
            key_handle, desired_access, object_attributes, title_index,
            class_name, create_options, disposition );
    }

    __forceinline std::int32_t query_value_key( void* key_handle, nt::unicode_string_t* value_name,
        std::uint32_t information_class, void* information, std::uint32_t length,
        std::uint32_t* result_length ) noexcept {
        using fn_t = std::int32_t( void*, nt::unicode_string_t*, std::uint32_t, void*,
            std::uint32_t, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_query_value_key,
            key_handle, value_name, information_class, information, length, result_length );
    }

    __forceinline std::int32_t set_value_key( void* key_handle, nt::unicode_string_t* value_name,
        std::uint32_t title_index, std::uint32_t type, void* data, std::uint32_t data_size ) noexcept {
        using fn_t = std::int32_t( void*, nt::unicode_string_t*, std::uint32_t,
            std::uint32_t, void*, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_set_value_key,
            key_handle, value_name, title_index, type, data, data_size );
    }

    __forceinline std::int32_t delete_value_key( void* key_handle,
        nt::unicode_string_t* value_name ) noexcept {
        using fn_t = std::int32_t( void*, nt::unicode_string_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_delete_value_key,
            key_handle, value_name );
    }

    __forceinline std::int32_t delete_key( void* key_handle ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_delete_key, key_handle );
    }

    __forceinline std::int32_t open_process( void** process_handle, std::uint32_t desired_access,
        nt::object_attributes_t* object_attributes, nt::client_id_t* client_id ) noexcept {
        using fn_t = std::int32_t( void**, std::uint32_t, nt::object_attributes_t*, nt::client_id_t* );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_open_process,
            process_handle, desired_access, object_attributes, client_id );
    }

    __forceinline std::int32_t terminate_process( void* process_handle, std::int32_t exit_status ) noexcept {
        using fn_t = std::int32_t( void*, std::int32_t );
        return symbols::call< fn_t >( symbols::get( ).m_zw.m_terminate_process,
            process_handle, exit_status );
    }

} // namespace kernel::api::zw