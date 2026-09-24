#pragma once

namespace kernel::api::ke {

    __forceinline void initialize_thread( void* thread, void* stack, void* start_routine,
        void* start_context, nt::context_t* context, void* teb, void* process ) noexcept {
        using fn_t = void( void*, void*, void*, void*, nt::context_t*, void*, void* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_initialize_thread,
            thread, stack, start_routine, start_context, context, teb, process );
    }

    __forceinline void start_thread( void* thread, void* param1, void* param2 ) noexcept {
        using fn_t = void( void*, void*, void* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_start_thread, thread, param1, param2 );
    }

    __forceinline void ready_thread( void* thread ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_ready_thread, thread );
    }

    __forceinline void stack_attach_process( void* process, nt::kapc_state_t* apc_state ) noexcept {
        using fn_t = void( void*, nt::kapc_state_t* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_stack_attach_process, process, apc_state );
    }

    __forceinline void unstack_detach_process( nt::kapc_state_t* apc_state ) noexcept {
        using fn_t = void( nt::kapc_state_t* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_unstack_detach_process, apc_state );
    }

    __forceinline std::uint32_t query_active_processor_count_ex( std::uint16_t group_number ) noexcept {
        using fn_t = std::uint32_t( std::uint16_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_query_active_processor_count_ex, group_number );
    }

    __forceinline std::uint32_t query_max_processor_count( std::uint16_t group = 0xFFFF ) noexcept {
        using fn_t = std::uint32_t( std::uint16_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_query_max_processor_count, group );
    }

    __forceinline std::uint64_t query_active_processors( ) noexcept {
        using fn_t = std::uint64_t( void );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_query_active_processors );
    }

    __forceinline std::uint32_t get_current_processor_number_ex( void* proc_number ) noexcept {
        using fn_t = std::uint32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_get_current_processor_number_ex, proc_number );
    }

    __forceinline std::uint64_t set_system_affinity_thread( std::uint64_t affinity ) noexcept {
        using fn_t = std::uint64_t( std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_set_system_affinity_thread, affinity );
    }

    __forceinline void revert_to_user_affinity_thread( ) noexcept {
        using fn_t = void( void );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_revert_to_user_affinity_thread );
    }

    __forceinline void set_target_processor_dpc( nt::kdpc_t* dpc, std::uint8_t number ) noexcept {
        using fn_t = void( nt::kdpc_t*, std::uint8_t );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_set_target_processor_dpc, dpc, number );
    }

    __forceinline std::uint8_t insert_queue_dpc( nt::kdpc_t* dpc, void* arg1, void* arg2 ) noexcept {
        using fn_t = std::uint8_t( nt::kdpc_t*, void*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_insert_queue_dpc, dpc, arg1, arg2 );
    }

    __forceinline std::uint8_t remove_queue_dpc( nt::kdpc_t* dpc ) noexcept {
        using fn_t = std::uint8_t( nt::kdpc_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_remove_queue_dpc, dpc );
    }

    __forceinline void initialize_dpc( nt::kdpc_t* dpc, void* routine, void* context ) noexcept {
        using fn_t = void( nt::kdpc_t*, void*, void* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_initialize_dpc, dpc, routine, context );
    }

    __forceinline std::uint8_t cancel_timer( nt::ktimer_t* timer ) noexcept {
        using fn_t = std::uint8_t( nt::ktimer_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_cancel_timer, timer );
    }

    __forceinline void set_disable_boost_thread( void* thread, bool disable ) noexcept {
        using fn_t = void( void*, bool );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_set_disable_boost_thread, thread, disable );
    }

    __forceinline void flush_entire_tb( bool invalidate, bool all_processors ) noexcept {
        using fn_t = void( bool, bool );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_flush_entire_tb, invalidate, all_processors );
    }

    __forceinline void flush_single_tb( std::uint64_t va, bool all_processors, bool invalidate ) noexcept {
        using fn_t = void( std::uint64_t, bool, bool );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_flush_single_tb, va, all_processors, invalidate );
    }

    __forceinline void invalidate_all_caches( ) noexcept {
        using fn_t = void( void );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_invalidate_all_caches );
    }

    __forceinline void* get_prcb( std::uint32_t number ) noexcept {
        using fn_t = void* ( std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_get_prcb, number );
    }

    __forceinline void* get_current_prcb( ) noexcept {
        using fn_t = void* ( void );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_get_current_prcb );
    }

    __forceinline void* service_descriptor_table( ) noexcept {
        const auto addr = symbols::get( ).m_ke.m_service_descriptor_table;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline void bug_check_ex( std::uint32_t code, std::uint64_t p1,
        std::uint64_t p2, std::uint64_t p3, std::uint64_t p4 ) noexcept {
        using fn_t = void( std::uint32_t, std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_bug_check_ex, code, p1, p2, p3, p4 );
    }

    __forceinline std::uint64_t ipi_generic_call( void* routine, std::uint64_t context ) noexcept {
        using fn_t = std::uint64_t( void*, std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_ipi_generic_call, routine, context );
    }

    __forceinline std::uint8_t raise_irql_to_dpc( ) noexcept {
        using fn_t = std::uint8_t( void );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_raise_irql_to_dpc_level );
    }

    __forceinline void lower_irql( std::uint8_t old_irql ) noexcept {
        using fn_t = void( std::uint8_t );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_lower_irql, old_irql );
    }

    __forceinline void acquire_spin_lock_at_dpc_level( void* lock ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_acquire_spin_lock_at_dpc_level, lock );
    }

    __forceinline void release_spin_lock_from_dpc_level( void* lock ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_release_spin_lock_from_dpc_level, lock );
    }

    __forceinline std::uint32_t get_current_processor_number( ) noexcept {
        using fn_t = std::uint32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_get_current_processor_number, nullptr );
    }

    __forceinline std::int32_t wait_for_single_object( void* object,
        std::uint32_t wait_reason, std::uint8_t wait_mode,
        std::uint8_t alertable, std::int64_t* timeout ) noexcept {
        using fn_t = std::int32_t( void*, std::uint32_t, std::uint8_t, std::uint8_t, std::int64_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_wait_for_single_object,
            object, wait_reason, wait_mode, alertable, timeout );
    }

    __forceinline std::int32_t wait_for_multiple_objects( std::uint32_t count,
        void** objects, std::uint32_t wait_type, std::uint32_t wait_reason,
        std::uint8_t wait_mode, std::uint8_t alertable, std::int64_t* timeout,
        void* wait_block_array ) noexcept {
        using fn_t = std::int32_t( std::uint32_t, void**, std::uint32_t, std::uint32_t,
            std::uint8_t, std::uint8_t, std::int64_t*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_wait_for_multiple_objects,
            count, objects, wait_type, wait_reason, wait_mode, alertable, timeout, wait_block_array );
    }

    __forceinline std::int32_t release_semaphore( void* semaphore,
        std::int32_t increment, std::int32_t adjustment, std::uint8_t wait ) noexcept {
        using fn_t = std::int32_t( void*, std::int32_t, std::int32_t, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_release_semaphore,
            semaphore, increment, adjustment, wait );
    }

    __forceinline std::int32_t release_mutex( void* mutex, std::uint8_t wait ) noexcept {
        using fn_t = std::int32_t( void*, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_release_mutex, mutex, wait );
    }

    __forceinline std::int32_t set_event( void* event, std::int32_t increment,
        std::uint8_t wait ) noexcept {
        using fn_t = std::int32_t( void*, std::int32_t, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_set_event, event, increment, wait );
    }

    __forceinline std::int32_t reset_event( void* event ) noexcept {
        using fn_t = std::int32_t( void* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_reset_event, event );
    }

    __forceinline void clear_event( void* event ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_clear_event, event );
    }

    __forceinline void initialize_event( void* event, std::uint32_t type, std::uint8_t state ) noexcept {
        using fn_t = void( void*, std::uint32_t, std::uint8_t );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_initialize_event, event, type, state );
    }

    __forceinline void initialize_semaphore( void* semaphore, std::int32_t count,
        std::int32_t limit ) noexcept {
        using fn_t = void( void*, std::int32_t, std::int32_t );
        symbols::call< fn_t >( symbols::get( ).m_ke.m_initialize_semaphore, semaphore, count, limit );
    }

    __forceinline std::int32_t delay_execution_thread( std::uint8_t wait_mode,
        std::uint8_t alertable, std::int64_t* interval ) noexcept {
        using fn_t = std::int32_t( std::uint8_t, std::uint8_t, std::int64_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_delay_execution_thread,
            wait_mode, alertable, interval );
    }

    __forceinline std::uint32_t query_time_increment( ) noexcept {
        using fn_t = std::uint32_t( void );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_query_time_increment );
    }

    __forceinline std::int64_t query_performance_counter( std::int64_t* frequency ) noexcept {
        using fn_t = std::int64_t( std::int64_t* );
        return symbols::call< fn_t >( symbols::get( ).m_ke.m_query_performance_counter, frequency );
    }

    __forceinline std::uint8_t current_irql( ) noexcept {
        return static_cast< std::uint8_t >( intrin::read_cr8( ) );
    }

    __forceinline void flush_caches_for( const void* va ) noexcept {
        flush_entire_tb( true, true );
        invalidate_all_caches( );
        flush_single_tb( reinterpret_cast< std::uint64_t >( va ), true, true );
    }

} // namespace kernel::api::ke