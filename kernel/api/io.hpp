#pragma once

namespace kernel::api::io {

    __forceinline std::int32_t create_device( nt::driver_object_t* driver_object,
        std::uint32_t device_extension_size, nt::unicode_string_t* device_name,
        std::uint32_t device_type, std::uint32_t device_characteristics,
        std::uint8_t exclusive, nt::device_object_t** device_object ) noexcept {
        using fn_t = std::int32_t( nt::driver_object_t*, std::uint32_t, nt::unicode_string_t*,
            std::uint32_t, std::uint32_t, std::uint8_t, nt::device_object_t** );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_create_device,
            driver_object, device_extension_size, device_name,
            device_type, device_characteristics, exclusive, device_object );
    }

    __forceinline void delete_device( nt::device_object_t* device_object ) noexcept {
        using fn_t = void( nt::device_object_t* );
        symbols::call< fn_t >( symbols::get( ).m_io.m_delete_device, device_object );
    }

    __forceinline std::int32_t create_symbolic_link( nt::unicode_string_t* symbolic_link_name,
        nt::unicode_string_t* device_name ) noexcept {
        using fn_t = std::int32_t( nt::unicode_string_t*, nt::unicode_string_t* );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_create_symbolic_link,
            symbolic_link_name, device_name );
    }

    __forceinline std::int32_t delete_symbolic_link( nt::unicode_string_t* symbolic_link_name ) noexcept {
        using fn_t = std::int32_t( nt::unicode_string_t* );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_delete_symbolic_link, symbolic_link_name );
    }

    __forceinline nt::mdl_t* allocate_mdl( void* virtual_address, std::uint32_t length,
        std::uint8_t secondary_buffer, std::uint8_t charge_quota, nt::irp_t* irp ) noexcept {
        using fn_t = nt::mdl_t* ( void*, std::uint32_t, std::uint8_t, std::uint8_t, nt::irp_t* );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_allocate_mdl,
            virtual_address, length, secondary_buffer, charge_quota, irp );
    }

    __forceinline void free_mdl( nt::mdl_t* mdl ) noexcept {
        using fn_t = void( nt::mdl_t* );
        symbols::call< fn_t >( symbols::get( ).m_io.m_free_mdl, mdl );
    }

    __forceinline nt::irp_t* build_synchronous_fsd_request( std::uint32_t major_function,
        nt::device_object_t* device_object, void* buffer, std::uint32_t length,
        nt::large_integer_t* starting_offset, nt::kevent_t* event,
        nt::io_status_block_t* io_status_block ) noexcept {
        using fn_t = nt::irp_t* ( std::uint32_t, nt::device_object_t*, void*, std::uint32_t,
            nt::large_integer_t*, nt::kevent_t*, nt::io_status_block_t* );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_build_synchronous_fsd_request,
            major_function, device_object, buffer, length,
            starting_offset, event, io_status_block );
    }

    __forceinline void* get_current_process( ) noexcept {
        using fn_t = void* ( void );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_get_current_process );
    }

    __forceinline std::int32_t get_device_object_pointer( nt::unicode_string_t* object_name,
        std::uint32_t desired_access, void** file_object, nt::device_object_t** device_object ) noexcept {
        using fn_t = std::int32_t( nt::unicode_string_t*, std::uint32_t, void**, nt::device_object_t** );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_get_device_object_pointer,
            object_name, desired_access, file_object, device_object );
    }

    __forceinline std::int32_t call_driver( nt::device_object_t* device_object, nt::irp_t* irp ) noexcept {
        using fn_t = std::int32_t( nt::device_object_t*, nt::irp_t* );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_call_driver, device_object, irp );
    }

    __forceinline void complete_request( nt::irp_t* irp, std::uint8_t priority_boost ) noexcept {
        using fn_t = void( nt::irp_t*, std::uint8_t );
        symbols::call< fn_t >( symbols::get( ).m_io.m_complete_request, irp, priority_boost );
    }

    __forceinline std::int32_t register_shutdown_notification( nt::device_object_t* device_object ) noexcept {
        using fn_t = std::int32_t( nt::device_object_t* );
        return symbols::call< fn_t >( symbols::get( ).m_io.m_register_shutdown_notification, device_object );
    }

} // namespace kernel::api::io