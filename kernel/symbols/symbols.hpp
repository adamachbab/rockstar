#pragma once

namespace kernel::symbols {

    struct sym_mm_t {
        std::uint64_t m_allocate_independent_pages;
        std::uint64_t m_free_independent_pages;
        std::uint64_t m_set_page_protection;
        std::uint64_t m_copy_memory;
        std::uint64_t m_copy_virtual_memory;
        std::uint64_t m_get_physical_address;
        std::uint64_t m_get_virtual_for_physical;
        std::uint64_t m_map_io_space;
        std::uint64_t m_map_io_space_ex;
        std::uint64_t m_unmap_io_space;
        std::uint64_t m_allocate_contiguous_memory;
        std::uint64_t m_allocate_contiguous_memory_specify_cache;
        std::uint64_t m_free_contiguous_memory;
        std::uint64_t m_is_address_valid;
        std::uint64_t m_get_system_routine_address;
        std::uint64_t m_get_physical_memory_ranges;
        std::uint64_t m_user_probe_address;
        std::uint64_t m_high_memory;
        std::uint64_t m_system_range_start;
        std::uint64_t m_initialize_process_address_space;
        std::uint64_t m_pfn_database;
        std::uint64_t m_unloaded_drivers;
        std::uint64_t m_last_unloaded_driver;
        std::uint64_t m_unloaded_driver_count;
        std::uint64_t m_pfn_lock;
        std::uint64_t m_allocate_pages_for_mdl;
        std::uint64_t m_free_pages_from_mdl;
        std::uint64_t m_map_locked_pages_specify_cache;
        std::uint64_t m_unmap_locked_pages;
        std::uint64_t m_probe_and_lock_pages;
        std::uint64_t m_unlock_pages;
        std::uint64_t m_build_mdl_for_non_paged_pool;
        std::uint64_t m_map_view_of_section;
        std::uint64_t m_unmap_view_of_section;
    };

    struct sym_mi_t {
        std::uint64_t m_lock_page_table_page;
        std::uint64_t m_is_page_on_bad_list;
        std::uint64_t m_make_page_bad;
        std::uint64_t m_copy_on_write;
        std::uint64_t m_remove_vad;
        std::uint64_t m_insert_vad;
        std::uint64_t m_get_pfn_from_page_table;
        std::uint64_t m_initialize_pfn_for_other_process;
        std::uint64_t m_allocate_vad;
        std::uint64_t m_delete_vad;
        std::uint64_t m_get_pte_address;
        std::uint64_t m_get_pde_address;
        std::uint64_t m_get_ppe_address;
        std::uint64_t m_get_pxe_address;
        std::uint64_t m_flush_tb_all;
    };

    struct sym_ps_t {
        std::uint64_t m_initial_system_process;
        std::uint64_t m_lookup_process_by_process_id;
        std::uint64_t m_lookup_thread_by_thread_id;
        std::uint64_t m_get_current_process;
        std::uint64_t m_get_current_thread;
        std::uint64_t m_get_process_id;
        std::uint64_t m_get_thread_id;
        std::uint64_t m_get_process_image_file_name;
        std::uint64_t m_get_process_peb;
        std::uint64_t m_get_process_wow64_process;
        std::uint64_t m_get_process_section_base_address;
        std::uint64_t m_get_process_session_id;
        std::uint64_t m_is_protected_process;
        std::uint64_t m_is_system_thread;
        std::uint64_t m_create_system_thread;
        std::uint64_t m_terminate_system_thread;
        std::uint64_t m_suspend_thread;
        std::uint64_t m_resume_thread;
        std::uint64_t m_get_context_thread;
        std::uint64_t m_set_context_thread;
        std::uint64_t m_set_create_process_notify_routine;
        std::uint64_t m_set_create_thread_notify_routine;
        std::uint64_t m_set_load_image_notify_routine;
        std::uint64_t m_remove_create_process_notify_routine;
        std::uint64_t m_remove_create_thread_notify_routine;
        std::uint64_t m_remove_load_image_notify_routine;
        std::uint64_t m_enum_process_threads;
        std::uint64_t m_loaded_module_list;
        std::uint64_t m_invert_process_map;
        std::uint64_t m_psp_allocate_thread;
        std::uint64_t m_psp_thread_delete;
        std::uint64_t m_psp_cid_table;
        std::uint64_t m_psp_create_process_notify_routine;
        std::uint64_t m_psp_create_thread_notify_routine;
        std::uint64_t m_psp_load_image_notify_routine;
    };

    struct sym_ke_t {
        std::uint64_t m_initialize_thread;
        std::uint64_t m_start_thread;
        std::uint64_t m_ready_thread;
        std::uint64_t m_stack_attach_process;
        std::uint64_t m_unstack_detach_process;
        std::uint64_t m_query_active_processor_count_ex;
        std::uint64_t m_query_max_processor_count;
        std::uint64_t m_query_active_processors;
        std::uint64_t m_get_current_processor_number_ex;
        std::uint64_t m_set_system_affinity_thread;
        std::uint64_t m_revert_to_user_affinity_thread;
        std::uint64_t m_set_target_processor_dpc;
        std::uint64_t m_insert_queue_dpc;
        std::uint64_t m_remove_queue_dpc;
        std::uint64_t m_initialize_dpc;
        std::uint64_t m_cancel_timer;
        std::uint64_t m_set_disable_boost_thread;
        std::uint64_t m_flush_entire_tb;
        std::uint64_t m_flush_single_tb;
        std::uint64_t m_invalidate_all_caches;
        std::uint64_t m_get_prcb;
        std::uint64_t m_get_current_prcb;
        std::uint64_t m_service_descriptor_table;
        std::uint64_t m_bug_check_ex;
        std::uint64_t m_ipi_generic_call;
        std::uint64_t m_raise_irql_to_dpc_level;
        std::uint64_t m_lower_irql;
        std::uint64_t m_acquire_spin_lock_at_dpc_level;
        std::uint64_t m_release_spin_lock_from_dpc_level;
        std::uint64_t m_get_current_processor_number;
        std::uint64_t m_wait_for_single_object;
        std::uint64_t m_wait_for_multiple_objects;
        std::uint64_t m_release_semaphore;
        std::uint64_t m_release_mutex;
        std::uint64_t m_set_event;
        std::uint64_t m_reset_event;
        std::uint64_t m_clear_event;
        std::uint64_t m_initialize_event;
        std::uint64_t m_initialize_semaphore;
        std::uint64_t m_delay_execution_thread;
        std::uint64_t m_query_time_increment;
        std::uint64_t m_query_performance_counter;
    };

    struct sym_ki_t {
        std::uint64_t m_system_call64;
        std::uint64_t m_system_call64_shadow;
        std::uint64_t m_nmi_callback_list_head;
        std::uint64_t m_service_table;
        std::uint64_t m_service_limit;
        std::uint64_t m_get_gdt_idt;
        std::uint64_t m_page_fault;
    };

    struct sym_kdp_t {
        std::uint64_t m_debug_routine_select;
        std::uint64_t m_trap;
        std::uint64_t m_report;
        std::uint64_t m_stub;
    };

    struct sym_ex_t {
        std::uint64_t m_allocate_pool_with_tag;
        std::uint64_t m_allocate_pool_with_quota_tag;
        std::uint64_t m_free_pool_with_tag;
        std::uint64_t m_query_big_pool_tag;
        std::uint64_t m_map_handle_to_pointer;
        std::uint64_t m_destroy_handle;
        std::uint64_t m_create_handle;
        std::uint64_t m_acquire_resource_exclusive_lite;
        std::uint64_t m_acquire_resource_shared_lite;
        std::uint64_t m_release_resource_lite;
        std::uint64_t m_acquire_push_lock_exclusive;
        std::uint64_t m_acquire_push_lock_shared;
        std::uint64_t m_release_push_lock_exclusive;
        std::uint64_t m_release_push_lock_shared;
        std::uint64_t m_p_pool_big_entry_size;
        std::uint64_t m_initialize_rundown_protection;
        std::uint64_t m_acquire_rundown_protection;
        std::uint64_t m_release_rundown_protection;
        std::uint64_t m_wait_for_rundown_protection_release;
        std::uint64_t m_query_wnf_state_data;
        std::uint64_t m_subscribe_wnf_state_change;
        std::uint64_t m_unsubscribe_wnf_state_change;
    };

    struct sym_ob_t {
        std::uint64_t m_dereference_object;
        std::uint64_t m_reference_object;
        std::uint64_t m_reference_object_by_handle;
        std::uint64_t m_reference_object_by_name;
        std::uint64_t m_open_object_by_pointer;
        std::uint64_t m_close_handle;
        std::uint64_t m_get_object_type;
        std::uint64_t m_query_name_string;
        std::uint64_t m_callback_list_head;
        std::uint64_t m_register_callbacks;
        std::uint64_t m_unregister_callbacks;
    };

    struct sym_rtl_t {
        std::uint64_t m_init_unicode_string;
        std::uint64_t m_init_ansi_string;
        std::uint64_t m_compare_unicode_string;
        std::uint64_t m_equal_unicode_string;
        std::uint64_t m_copy_unicode_string;
        std::uint64_t m_free_unicode_string;
        std::uint64_t m_unicode_string_to_ansi_string;
        std::uint64_t m_ansi_string_to_unicode_string;
        std::uint64_t m_create_user_thread;
        std::uint64_t m_get_version;
        std::uint64_t m_lookup_element_generic_table_avl;
        std::uint64_t m_delete_element_generic_table_avl;
        std::uint64_t m_insert_element_generic_table_avl;
        std::uint64_t m_enumerate_generic_table_avl;
        std::uint64_t m_get_element_generic_table_avl;
        std::uint64_t m_number_generic_table_elements_avl;
        std::uint64_t m_debug_print_callback_list;
        std::uint64_t m_pc_to_file_header;
    };

    struct sym_io_t {
        std::uint64_t m_create_device;
        std::uint64_t m_delete_device;
        std::uint64_t m_create_symbolic_link;
        std::uint64_t m_delete_symbolic_link;
        std::uint64_t m_allocate_mdl;
        std::uint64_t m_free_mdl;
        std::uint64_t m_build_synchronous_fsd_request;
        std::uint64_t m_get_current_process;
        std::uint64_t m_get_device_object_pointer;
        std::uint64_t m_call_driver;
        std::uint64_t m_complete_request;
        std::uint64_t m_register_shutdown_notification;
    };

    struct sym_zw_t {
        std::uint64_t m_query_system_information;
        std::uint64_t m_close;
        std::uint64_t m_create_file;
        std::uint64_t m_read_file;
        std::uint64_t m_write_file;
        std::uint64_t m_open_key;
        std::uint64_t m_create_key;
        std::uint64_t m_query_value_key;
        std::uint64_t m_set_value_key;
        std::uint64_t m_delete_value_key;
        std::uint64_t m_delete_key;
        std::uint64_t m_open_process;
        std::uint64_t m_terminate_process;
    };

    struct sym_dbg_t {
        std::uint64_t m_print;
        std::uint64_t m_print_ex;
        std::uint64_t m_nt_global_flag;
        std::uint64_t m_break_point;
        std::uint64_t m_query_debug_filter_state;
        std::uint64_t m_set_debug_filter_state;
    };

    struct sym_misc_t {
        std::uint64_t m_hal_private_dispatch_table;
        std::uint64_t m_etw_trace_silo_kernel_event;
        std::uint64_t m_po_idle;
        std::uint64_t m_ci_options;
        std::uint64_t m_pool_big_page_table;
        std::uint64_t m_pool_big_page_table_size;
        std::uint64_t m_piddb_cache_table;
        std::uint64_t m_piddb_lock;
        std::uint64_t m_expected_ci_g_pfn;
    };

    struct sym_crt_t {
        std::uint64_t m_memcpy;
        std::uint64_t m_memset;
        std::uint64_t m_memmove;
        std::uint64_t m_memcmp;
        std::uint64_t m_strcmp;
        std::uint64_t m_strncmp;
        std::uint64_t m_strlen;
        std::uint64_t m_strcpy;
        std::uint64_t m_strncpy;
        std::uint64_t m_wcslen;
        std::uint64_t m_wcscmp;
        std::uint64_t m_wcscpy;
    };

    struct sym_offsets_t {
        std::uint32_t m_vad_root;
        std::uint32_t m_directory_table;
        std::uint32_t m_active_process_links;
        std::uint32_t m_image_file_name;
        std::uint32_t m_image_file_pointer;
        std::uint32_t m_thread_list_head;
        std::uint32_t m_unique_process_id;
        std::uint32_t m_peb;
        std::uint32_t m_wow64_process;
        std::uint32_t m_section_object;
        std::uint32_t m_section_base_address;
        std::uint32_t m_pool_big_entry_size;
        std::uint32_t m_kthread_process;
        std::uint32_t m_kthread_apc_state;
        std::uint32_t m_kthread_previous_mode;
        std::uint32_t m_ethread_cid;
        std::uint32_t m_object_header_body;
    };

    struct symbols_t {
        sym_mm_t      m_mm;
        sym_mi_t      m_mi;
        sym_ps_t      m_ps;
        sym_ke_t      m_ke;
        sym_ki_t      m_ki;
        sym_kdp_t     m_kdp;
        sym_ex_t      m_ex;
        sym_ob_t      m_ob;
        sym_rtl_t     m_rtl;
        sym_io_t      m_io;
        sym_zw_t      m_zw;
        sym_dbg_t     m_dbg;
        sym_misc_t    m_misc;
        sym_crt_t     m_crt;
        sym_offsets_t m_offsets;
        std::uint32_t m_build_number;

        constexpr bool is_valid( ) const noexcept {
            return m_mm.m_allocate_independent_pages != 0
                && m_ki.m_system_call64 != 0
                && m_dbg.m_print_ex != 0;
        }

        constexpr bool has( std::uint64_t symbol ) const noexcept {
            return symbol != 0;
        }
    };

    struct entry_t {
        symbols_t     m_pdb;
        std::uint64_t m_image_base;
        std::uint64_t m_image_size;
        std::uint64_t m_ntoskrnl_base;
        std::uint64_t m_directory_table_base;
        std::uint64_t m_rdata_offset;
        std::uint64_t m_rdata_size;
        std::uint64_t m_data_offset;
        std::uint64_t m_data_size;

        constexpr bool is_valid( ) const noexcept {
            return m_image_base != 0
                && m_image_size != 0
                && m_ntoskrnl_base != 0
                && m_pdb.is_valid( );
        }
    };

    extern symbols_t     m_symbols;
    extern std::uint64_t m_image_base;
    extern std::uint64_t m_image_size;
    extern std::uint64_t m_ntoskrnl_base;
    extern std::uint64_t m_directory_table_base;

    template<class T> struct is_void_type { static constexpr bool value = false; };
    template<>        struct is_void_type<void> { static constexpr bool value = true; };
    template<class fn_t, class... args_t>
    __forceinline auto call( std::uint64_t addr, args_t... args ) noexcept
        -> decltype( reinterpret_cast< fn_t* >( addr )( args... ) ) {
        using ret_t = decltype( reinterpret_cast< fn_t* >( addr )( args... ) );
        if constexpr ( is_void_type< ret_t >::value ) {
            if ( addr ) reinterpret_cast< fn_t* >( addr )( args... );
            return;
        }
        else {
            if ( !addr ) return ret_t{ };
            return reinterpret_cast< fn_t* >( addr )( args... );
        }
    }

    bool             initialize( const entry_t* entry ) noexcept;
    const symbols_t& get( ) noexcept;
    std::uint64_t    image_base( ) noexcept;
    std::uint64_t    image_size( ) noexcept;
    std::uint64_t    ntoskrnl_base( ) noexcept;
    std::uint64_t    directory_table_base( ) noexcept;

} // namespace kernel::symbols