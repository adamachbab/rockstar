#pragma once

namespace kernel::api::ex {

    __forceinline void* allocate_pool( std::uint32_t pool_type, std::size_t size,
        std::uint32_t tag = 'vnvD' ) noexcept {
        using fn_t = void* ( std::uint32_t, std::size_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_allocate_pool_with_tag,
            pool_type, size, tag );
    }

    __forceinline void* allocate_pool_with_quota( std::uint32_t pool_type, std::size_t size,
        std::uint32_t tag = 'vnvD' ) noexcept {
        using fn_t = void* ( std::uint32_t, std::size_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_allocate_pool_with_quota_tag,
            pool_type, size, tag );
    }

    __forceinline void free_pool( void* p, std::uint32_t tag = 'vnvD' ) noexcept {
        using fn_t = void( void*, std::uint32_t );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_free_pool_with_tag, p, tag );
    }

    __forceinline std::int32_t query_big_pool_tag( void* pool_information,
        std::uint32_t information_length, std::uint32_t* return_length ) noexcept {
        using fn_t = std::int32_t( void*, std::uint32_t, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_query_big_pool_tag,
            pool_information, information_length, return_length );
    }

    __forceinline void* map_handle_to_pointer( void* handle_table, void* handle ) noexcept {
        using fn_t = void* ( void*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_map_handle_to_pointer,
            handle_table, handle );
    }

    __forceinline bool destroy_handle( void* handle_table, void* handle, void* entry ) noexcept {
        using fn_t = bool( void*, void*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_destroy_handle,
            handle_table, handle, entry );
    }

    __forceinline std::int32_t create_handle( void* handle_table, void* entry, void** handle ) noexcept {
        using fn_t = std::int32_t( void*, void*, void** );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_create_handle,
            handle_table, entry, handle );
    }

    __forceinline bool acquire_resource_exclusive_lite( nt::eresource_t* resource,
        std::uint8_t wait ) noexcept {
        using fn_t = bool( nt::eresource_t*, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_acquire_resource_exclusive_lite,
            resource, wait );
    }

    __forceinline bool acquire_resource_shared_lite( nt::eresource_t* resource,
        std::uint8_t wait ) noexcept {
        using fn_t = bool( nt::eresource_t*, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_acquire_resource_shared_lite,
            resource, wait );
    }

    __forceinline void release_resource_lite( nt::eresource_t* resource ) noexcept {
        using fn_t = void( nt::eresource_t* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_release_resource_lite, resource );
    }

    __forceinline void acquire_push_lock_exclusive( void* lock ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_acquire_push_lock_exclusive, lock );
    }

    __forceinline void acquire_push_lock_shared( void* lock ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_acquire_push_lock_shared, lock );
    }

    __forceinline void release_push_lock_exclusive( void* lock ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_release_push_lock_exclusive, lock );
    }

    __forceinline void release_push_lock_shared( void* lock ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_release_push_lock_shared, lock );
    }

    __forceinline std::uint32_t pool_big_entry_size( ) noexcept {
        const auto addr = symbols::get( ).m_ex.m_p_pool_big_entry_size;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint32_t* >( addr );
    }

    __forceinline void initialize_rundown_protection( void* rundown ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_initialize_rundown_protection, rundown );
    }

    __forceinline std::uint8_t acquire_rundown_protection( void* rundown ) noexcept {
        using fn_t = std::uint8_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_acquire_rundown_protection, rundown );
    }

    __forceinline void release_rundown_protection( void* rundown ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_release_rundown_protection, rundown );
    }

    __forceinline void wait_for_rundown_protection_release( void* rundown ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ex.m_wait_for_rundown_protection_release, rundown );
    }

    __forceinline std::int32_t query_wnf_state_data( void* wnf_struct,
        std::uint32_t* change_stamp, void* buffer, std::uint32_t* buffer_size ) noexcept {
        using fn_t = std::int32_t( void*, std::uint32_t*, void*, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_query_wnf_state_data,
            wnf_struct, change_stamp, buffer, buffer_size );
    }

    __forceinline std::int32_t subscribe_wnf_state_change( void** subscription,
        const nt::wnf_state_name_t* state_name, std::uint32_t change_stamp,
        void* type_id, nt::wnf_user_callback_t callback, void* callback_context ) noexcept {
        using fn_t = std::int32_t( void**, const nt::wnf_state_name_t*,
            std::uint32_t, void*, nt::wnf_user_callback_t, void* );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_subscribe_wnf_state_change,
            subscription, state_name, change_stamp, type_id, callback, callback_context );
    }

    __forceinline std::int32_t unsubscribe_wnf_state_change( void* subscription ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ex.m_unsubscribe_wnf_state_change,
            subscription );
    }

} // namespace kernel::api::ex