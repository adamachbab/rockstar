#pragma once

namespace kernel::api::ob {

    __forceinline void dereference_object( void* object ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ob.m_dereference_object, object );
    }

    __forceinline std::int64_t reference_object( void* object ) noexcept {
        using fn_t = std::int64_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_reference_object, object );
    }

    __forceinline std::int32_t reference_object_by_handle( void* handle,
        std::uint32_t desired_access, void* object_type, std::uint8_t access_mode,
        void** object, void* handle_information ) noexcept {
        using fn_t = std::int32_t( void*, std::uint32_t, void*, std::uint8_t, void**, void* );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_reference_object_by_handle,
            handle, desired_access, object_type, access_mode, object, handle_information );
    }

    __forceinline std::int32_t reference_object_by_name( nt::unicode_string_t* object_name,
        std::uint32_t attributes, void* access_state, std::uint32_t desired_access,
        void* object_type, std::uint8_t access_mode, void* parse_context, void** object ) noexcept {
        using fn_t = std::int32_t( nt::unicode_string_t*, std::uint32_t, void*, std::uint32_t,
            void*, std::uint8_t, void*, void** );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_reference_object_by_name,
            object_name, attributes, access_state, desired_access, object_type,
            access_mode, parse_context, object );
    }

    __forceinline std::int32_t open_object_by_pointer( void* object,
        std::uint32_t attributes, void* access_state, std::uint32_t desired_access,
        void* object_type, std::uint8_t access_mode, void** handle ) noexcept {
        using fn_t = std::int32_t( void*, std::uint32_t, void*, std::uint32_t, void*, std::uint8_t, void** );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_open_object_by_pointer,
            object, attributes, access_state, desired_access, object_type, access_mode, handle );
    }

    __forceinline std::int32_t close_handle( void* handle ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_close_handle, handle );
    }

    __forceinline nt::object_type_t* get_object_type( void* object ) noexcept {
        using fn_t = nt::object_type_t* ( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_get_object_type, object );
    }

    __forceinline std::int32_t query_name_string( void* object, void* object_name_info,
        std::uint32_t length, std::uint32_t* return_length ) noexcept {
        using fn_t = std::int32_t( void*, void*, std::uint32_t, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_query_name_string,
            object, object_name_info, length, return_length );
    }

    __forceinline nt::list_entry_t* callback_list_head( ) noexcept {
        const auto addr = symbols::get( ).m_ob.m_callback_list_head;
        return addr ? reinterpret_cast< nt::list_entry_t* >( addr ) : nullptr;
    }

    __forceinline std::int32_t register_callbacks( void* callback_registration,
        void** registration_handle ) noexcept {
        using fn_t = std::int32_t( void*, void** );
        return symbols::call< fn_t >( symbols::get( ).m_ob.m_register_callbacks,
            callback_registration, registration_handle );
    }

    __forceinline void unregister_callbacks( void* registration_handle ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ob.m_unregister_callbacks, registration_handle );
    }

} // namespace kernel::api::ob