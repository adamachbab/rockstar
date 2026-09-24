#pragma once

namespace kernel::api::ps {

    __forceinline void* initial_system_process( ) noexcept {
        const auto addr = symbols::get( ).m_ps.m_initial_system_process;
        if ( !addr ) return nullptr;
        return *reinterpret_cast< void** >( addr );
    }

    __forceinline std::int32_t lookup_process_by_pid( std::uint32_t pid, void** process ) noexcept {
        using fn_t = std::int32_t( void*, void** );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_lookup_process_by_process_id,
            reinterpret_cast< void* >( static_cast< std::uint64_t >( pid ) ), process );
    }

    __forceinline std::int32_t lookup_thread_by_tid( std::uint32_t tid, void** thread ) noexcept {
        using fn_t = std::int32_t( void*, void** );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_lookup_thread_by_thread_id,
            reinterpret_cast< void* >( static_cast< std::uint64_t >( tid ) ), thread );
    }

    __forceinline void* get_current_process( ) noexcept {
        using fn_t = void* ( void );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_current_process );
    }

    __forceinline void* get_current_thread( ) noexcept {
        using fn_t = void* ( void );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_current_thread );
    }

    __forceinline std::uint32_t get_process_id( void* eprocess ) noexcept {
        using fn_t = std::uint32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_process_id, eprocess );
    }

    __forceinline std::uint32_t get_thread_id( void* thread ) noexcept {
        using fn_t = std::uint32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_thread_id, thread );
    }

    __forceinline const char* get_process_image_file_name( void* eprocess ) noexcept {
        using fn_t = const char* ( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_process_image_file_name, eprocess );
    }

    __forceinline void* get_process_peb( void* eprocess ) noexcept {
        using fn_t = void* ( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_process_peb, eprocess );
    }

    __forceinline void* get_process_wow64_process( void* eprocess ) noexcept {
        using fn_t = void* ( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_process_wow64_process, eprocess );
    }

    __forceinline void* get_process_section_base_address( void* eprocess ) noexcept {
        using fn_t = void* ( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_process_section_base_address, eprocess );
    }

    __forceinline std::uint32_t get_process_session_id( void* eprocess ) noexcept {
        using fn_t = std::uint32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_process_session_id, eprocess );
    }

    __forceinline bool is_protected_process( void* eprocess ) noexcept {
        using fn_t = bool( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_is_protected_process, eprocess );
    }

    __forceinline bool is_system_thread( void* ethread ) noexcept {
        using fn_t = bool( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_is_system_thread, ethread );
    }

    __forceinline std::int32_t create_system_thread(
        void** thread_handle,
        std::uint32_t desired_access,
        void* object_attributes,
        void* process_handle,
        nt::client_id_t* client_id,
        void ( *start_routine )( void* start_context ),
        void* start_context ) noexcept {
        using fn_t = std::int32_t( void**, std::uint32_t, void*, void*, nt::client_id_t*,
            void ( * )( void* ), void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_create_system_thread,
            thread_handle, desired_access, object_attributes,
            process_handle, client_id, start_routine, start_context );
    }

    __forceinline std::int32_t terminate_system_thread( std::int32_t exit_status ) noexcept {
        using fn_t = std::int32_t( std::int32_t );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_terminate_system_thread, exit_status );
    }

    __forceinline std::int32_t suspend_thread( void* thread, std::uint32_t* previous_count ) noexcept {
        using fn_t = std::int32_t( void*, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_suspend_thread, thread, previous_count );
    }

    __forceinline std::int32_t resume_thread( void* thread, std::uint32_t* previous_count ) noexcept {
        using fn_t = std::int32_t( void*, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_resume_thread, thread, previous_count );
    }

    __forceinline std::int32_t get_context_thread( void* thread, nt::context_t* context ) noexcept {
        using fn_t = std::int32_t( void*, nt::context_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_get_context_thread, thread, context );
    }

    __forceinline std::int32_t set_context_thread( void* thread, nt::context_t* context ) noexcept {
        using fn_t = std::int32_t( void*, nt::context_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_set_context_thread, thread, context );
    }

    __forceinline std::int32_t set_create_process_notify_routine( void* routine, bool remove ) noexcept {
        using fn_t = std::int32_t( void*, bool );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_set_create_process_notify_routine,
            routine, remove );
    }

    __forceinline std::int32_t set_create_thread_notify_routine( void* routine ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_set_create_thread_notify_routine, routine );
    }

    __forceinline std::int32_t set_load_image_notify_routine( void* routine ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_set_load_image_notify_routine, routine );
    }

    __forceinline std::int32_t remove_create_process_notify_routine( void* routine ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_remove_create_process_notify_routine, routine );
    }

    __forceinline std::int32_t remove_create_thread_notify_routine( void* routine ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_remove_create_thread_notify_routine, routine );
    }

    __forceinline std::int32_t remove_load_image_notify_routine( void* routine ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_remove_load_image_notify_routine, routine );
    }

    __forceinline std::int32_t enum_process_threads( void* process, void** thread_list,
        std::uint32_t* count ) noexcept {
        using fn_t = std::int32_t( void*, void**, std::uint32_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_enum_process_threads,
            process, thread_list, count );
    }

    __forceinline nt::list_entry_t* loaded_module_list( ) noexcept {
        const auto addr = symbols::get( ).m_ps.m_loaded_module_list;
        return addr ? reinterpret_cast< nt::list_entry_t* >( addr ) : nullptr;
    }

    __forceinline void* invert_process_map( ) noexcept {
        const auto addr = symbols::get( ).m_ps.m_invert_process_map;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline std::int32_t psp_allocate_thread( std::uint64_t process, std::uint32_t oa_flags,
        bool is_user_thread, void* user_stack, void* initial_teb, void* context_frame,
        void* start_routine, void* start_context, std::uint32_t* flags, void** out_thread,
        void* client_id, void* output_buffer ) noexcept {
        using fn_t = std::int32_t( std::uint64_t, std::uint32_t, bool, void*, void*, void*, void*, void*,
            std::uint32_t*, void**, void*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_ps.m_psp_allocate_thread,
            process, oa_flags, is_user_thread, user_stack, initial_teb, context_frame,
            start_routine, start_context, flags, out_thread, client_id, output_buffer );
    }

    __forceinline void psp_thread_delete( void* thread ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ps.m_psp_thread_delete, thread );
    }

    __forceinline void* psp_cid_table( ) noexcept {
        const auto addr = symbols::get( ).m_ps.m_psp_cid_table;
        if ( !addr ) return nullptr;
        return *reinterpret_cast< void** >( addr );
    }

    __forceinline nt::ex_callback_routine_block_t** psp_create_process_notify_routine( ) noexcept {
        const auto addr = symbols::get( ).m_ps.m_psp_create_process_notify_routine;
        return addr ? reinterpret_cast< nt::ex_callback_routine_block_t** >( addr ) : nullptr;
    }

    __forceinline nt::ex_callback_routine_block_t** psp_create_thread_notify_routine( ) noexcept {
        const auto addr = symbols::get( ).m_ps.m_psp_create_thread_notify_routine;
        return addr ? reinterpret_cast< nt::ex_callback_routine_block_t** >( addr ) : nullptr;
    }

    __forceinline nt::ex_callback_routine_block_t** psp_load_image_notify_routine( ) noexcept {
        const auto addr = symbols::get( ).m_ps.m_psp_load_image_notify_routine;
        return addr ? reinterpret_cast< nt::ex_callback_routine_block_t** >( addr ) : nullptr;
    }

} // namespace kernel::api::ps