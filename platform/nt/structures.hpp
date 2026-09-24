#pragma once

namespace nt {

    template<typename record_t, typename field_t>
    __forceinline record_t* containing_record( field_t* address, std::uint64_t field_offset ) noexcept {
        return reinterpret_cast< record_t* >(
            reinterpret_cast< std::uint8_t* >( address ) - field_offset );
    }

    template<typename T, typename M>
    __forceinline constexpr std::uint64_t field_offset_of( M T::* member ) noexcept {
        return reinterpret_cast< std::uint64_t >(
            &( reinterpret_cast< T* >( 0 )->*member ) );
    }

    struct list_entry_t {
        list_entry_t* m_flink;
        list_entry_t* m_blink;
    };

    struct single_list_entry_t {
        single_list_entry_t* m_next;
    };

    struct slist_header_t {
        std::uint64_t m_alignment;
        std::uint64_t m_region;
    };

    struct rtl_balanced_node_t {
        union {
            rtl_balanced_node_t* m_children[ 2 ];
            struct {
                rtl_balanced_node_t* m_left;
                rtl_balanced_node_t* m_right;
            };
        };
        std::uint64_t m_parent_value;
    };

    struct rtl_avl_tree_t {
        rtl_balanced_node_t* m_root;
    };

    struct rtl_rb_tree_t {
        rtl_balanced_node_t* m_root;
        rtl_balanced_node_t* m_min;
    };

    struct rtl_balanced_links_t {
        void* m_parent;
        void* m_left;
        void* m_right;
        std::uint8_t  m_balance;
        std::uint8_t  m_reserved[ 3 ];
        std::uint32_t m_pad;
    };

    struct rtl_avl_table_t {
        rtl_balanced_links_t m_balanced_root;
        void* m_ordered_pointer;
        std::uint32_t        m_which_ordered_element;
        std::uint32_t        m_number_generic_table_elements;
        std::uint32_t        m_depth_of_tree;
        std::uint32_t        m_pad;
        void* m_restart_key;
        std::uint32_t        m_delete_count;
        std::uint32_t        m_pad2;
        void* m_compare_routine;
        void* m_allocate_routine;
        void* m_free_routine;
        void* m_table_context;
    };

    struct unicode_string_t {
        std::uint16_t     m_length;
        std::uint16_t     m_maximum_length;
        std::wchar_alias* m_buffer;
    };

    struct ansi_string_t {
        std::uint16_t m_length;
        std::uint16_t m_maximum_length;
        char* m_buffer;
    };

    struct oem_string_t {
        std::uint16_t m_length;
        std::uint16_t m_maximum_length;
        char* m_buffer;
    };

    struct string_t {
        std::uint16_t m_length;
        std::uint16_t m_maximum_length;
        char* m_buffer;
    };

    union large_integer_t {
        struct {
            std::uint32_t m_low_part;
            std::int32_t  m_high_part;
        };
        std::int64_t m_quad_part;
    };

    union ularge_integer_t {
        struct {
            std::uint32_t m_low_part;
            std::uint32_t m_high_part;
        };
        std::uint64_t m_quad_part;
    };

    struct client_id_t {
        void* m_unique_process;
        void* m_unique_thread;
    };

    struct object_attributes_t {
        std::uint32_t     m_length;
        void* m_root_directory;
        unicode_string_t* m_object_name;
        std::uint32_t     m_attributes;
        void* m_security_descriptor;
        void* m_security_quality_of_service;
    };

    struct io_status_block_t {
        union {
            ntstatus_t m_status;
            void* m_pointer;
        };
        std::uint64_t m_information;
    };

    struct kldr_data_table_entry_t {
        list_entry_t     m_in_load_order_links;
        void* m_exception_table;
        std::uint32_t    m_exception_table_size;
        void* m_gp_value;
        void* m_non_paged_debug_info;
        void* m_dll_base;
        void* m_entry_point;
        std::uint32_t    m_size_of_image;
        unicode_string_t m_full_dll_name;
        unicode_string_t m_base_dll_name;
        std::uint32_t    m_flags;
        std::uint16_t    m_load_count;
        std::uint16_t    m_tls_index_or_flags;
        void* m_section_pointer;
        std::uint32_t    m_check_sum;
        std::uint32_t    m_time_date_stamp;
        void* m_loaded_imports;
        void* m_patch_information;
    };

    struct mmpfn_entry1_t {
        std::uint8_t m_page_location : 3;
        std::uint8_t m_write_in_progress : 1;
        std::uint8_t m_modified : 1;
        std::uint8_t m_read_in_progress : 1;
        std::uint8_t m_cache_attribute : 2;
    };

    struct mmpfn_entry3_t {
        std::uint8_t m_priority : 3;
        std::uint8_t m_on_protected_standby : 1;
        std::uint8_t m_in_page_error : 1;
        std::uint8_t m_system_charged_page : 1;
        std::uint8_t m_removal_requested : 1;
        std::uint8_t m_parity_error : 1;
    };

    struct mmpfn_t {
        union {
            list_entry_t        m_list_entry;
            rtl_balanced_node_t m_tree_node;
            struct {
                void* m_next;
                void* m_pte_address;
                std::uint64_t m_original_pte;
            };
        };
        std::uint64_t m_u2;
        union {
            struct {
                std::uint16_t  m_reference_count;
                mmpfn_entry1_t m_e1;
                std::uint8_t   m_pad;
            };
            struct {
                std::uint16_t  m_ref_pad;
                mmpfn_entry3_t m_e3;
                std::uint8_t   m_pad_2;
            };
        } m_u3;
        std::uint16_t m_node_blink_low;
        std::uint16_t m_flags16;
        std::uint16_t m_view_count;
        std::uint64_t m_u5;
        struct {
            std::uint64_t m_pte_frame : 36;
            std::uint64_t m_resident_page : 1;
            std::uint64_t m_unused1 : 1;
            std::uint64_t m_unused2 : 1;
            std::uint64_t m_partition : 10;
            std::uint64_t m_file_only : 1;
            std::uint64_t m_pfn_exists : 1;
            std::uint64_t m_node_flink_high : 5;
            std::uint64_t m_page_identity : 3;
            std::uint64_t m_prototype_pte : 1;
            std::uint64_t m_entire_field_hi : 4;
        } m_u4;
    };

    struct mmpte_hardware_t {
        std::uint64_t m_present : 1;
        std::uint64_t m_read_write : 1;
        std::uint64_t m_user_supervisor : 1;
        std::uint64_t m_page_write_through : 1;
        std::uint64_t m_page_cache_disable : 1;
        std::uint64_t m_accessed : 1;
        std::uint64_t m_dirty : 1;
        std::uint64_t m_page_size_or_pat : 1;
        std::uint64_t m_global : 1;
        std::uint64_t m_ignored_1 : 3;
        std::uint64_t m_pfn : 36;
        std::uint64_t m_reserved : 4;
        std::uint64_t m_ignored_2 : 11;
        std::uint64_t m_no_execute : 1;
    };

    union pml4e_t {
        struct {
            std::uint64_t m_present : 1;
            std::uint64_t m_read_write : 1;
            std::uint64_t m_user_supervisor : 1;
            std::uint64_t m_page_write_through : 1;
            std::uint64_t m_page_cache_disable : 1;
            std::uint64_t m_accessed : 1;
            std::uint64_t m_dirty : 1;
            std::uint64_t m_page_size : 1;
            std::uint64_t m_global : 1;
            std::uint64_t m_ignored_1 : 3;
            std::uint64_t m_pfn : 36;
            std::uint64_t m_reserved : 4;
            std::uint64_t m_ignored_2 : 11;
            std::uint64_t m_no_execute : 1;
        } m_hard;
        std::uint64_t m_flags;
    };

    using pdpte_t = pml4e_t;
    using pde_t = pml4e_t;

    union pte_t {
        struct {
            std::uint64_t m_present : 1;
            std::uint64_t m_read_write : 1;
            std::uint64_t m_user_supervisor : 1;
            std::uint64_t m_page_write_through : 1;
            std::uint64_t m_page_cache_disable : 1;
            std::uint64_t m_accessed : 1;
            std::uint64_t m_dirty : 1;
            std::uint64_t m_pat : 1;
            std::uint64_t m_global : 1;
            std::uint64_t m_ignored_1 : 3;
            std::uint64_t m_pfn : 36;
            std::uint64_t m_reserved : 4;
            std::uint64_t m_ignored_2 : 7;
            std::uint64_t m_protection_key : 4;
            std::uint64_t m_no_execute : 1;
        } m_hard;
        std::uint64_t m_flags;
    };

    struct kprocess_t;
    struct eprocess_t;
    struct kthread_t;
    struct ethread_t;
    struct kpcr_t;
    struct kprcb_t;

    struct kapc_state_t {
        list_entry_t m_apc_list_head[ 2 ];
        kprocess_t* m_process;
        union {
            std::uint8_t m_in_progress_flags;
            struct {
                std::uint8_t m_kernel_apc_in_progress : 1;
                std::uint8_t m_special_apc_in_progress : 1;
            };
        };
        std::uint8_t m_kernel_apc_pending;
        union {
            std::uint8_t m_user_apc_pending_all;
            struct {
                std::uint8_t m_special_user_apc_pending : 1;
                std::uint8_t m_user_apc_pending : 1;
            };
        };
    };

    struct kapc_t {
        std::uint8_t  m_type;
        std::uint8_t  m_spare_byte0;
        std::uint8_t  m_size;
        std::uint8_t  m_spare_byte1;
        std::uint32_t m_spare_long0;
        void* m_thread;
        list_entry_t  m_apc_list_entry;
        void* m_reserved[ 3 ];
        void* m_normal_context;
        void* m_system_argument1;
        void* m_system_argument2;
        std::uint8_t  m_apc_state_index;
        std::uint8_t  m_apc_mode;
        std::uint8_t  m_inserted;
    };

    struct mmvad_short_t {
        rtl_balanced_node_t m_vad_node;
        std::uint32_t       m_starting_vpn;
        std::uint32_t       m_ending_vpn;
        std::uint8_t        m_starting_vpn_high;
        std::uint8_t        m_ending_vpn_high;
        std::uint8_t        m_commit_charge_bits[ 2 ];
        std::uint32_t       m_reference_count;
        std::uint64_t       m_push_lock;
    };

    struct mmvad_flags_t {
        std::uint32_t m_lock : 1;
        std::uint32_t m_lock_contended : 1;
        std::uint32_t m_delete_in_progress : 1;
        std::uint32_t m_no_change : 1;
        std::uint32_t m_vad_type : 3;
        std::uint32_t m_protection : 5;
        std::uint32_t m_preferred_node : 6;
        std::uint32_t m_page_size : 2;
        std::uint32_t m_private_memory : 1;
    };

    struct mmvad_flags1_t {
        std::uint32_t m_commit_charge : 31;
        std::uint32_t m_mem_commit : 1;
    };

    struct mm_unloaded_driver_t {
        unicode_string_t m_name;
        void* m_start_address;
        void* m_end_address;
        std::uint64_t    m_current_time;
    };

    struct piddb_cache_entry_t {
        list_entry_t     m_list;
        unicode_string_t m_driver_name;
        std::uint32_t    m_time_date_stamp;
        std::int32_t     m_load_status;
        std::uint8_t     m_padding[ 16 ];
    };

    struct ex_callback_routine_block_t {
        std::uint64_t m_ref_count;
        void* m_function;
        void* m_context;
    };

    struct ex_fast_ref_t {
        union {
            void* m_object;
            std::uint64_t m_ref_cnt : 4;
            std::uint64_t m_value;
        };
    };

    struct rtl_process_module_information_t {
        void* m_section;
        void* m_mapped_base;
        void* m_image_base;
        std::uint32_t m_image_size;
        std::uint32_t m_flags;
        std::uint16_t m_load_order_index;
        std::uint16_t m_init_order_index;
        std::uint16_t m_load_count;
        std::uint16_t m_offset_to_file_name;
        std::uint8_t  m_full_path_name[ 256 ];
    };

    struct rtl_process_modules_t {
        std::uint32_t                    m_number_of_modules;
        rtl_process_module_information_t m_modules[ 1 ];
    };

    struct system_handle_entry_t {
        std::uint16_t m_owner_pid;
        std::uint16_t m_creator_back_trace_index;
        std::uint8_t  m_object_type;
        std::uint8_t  m_handle_attributes;
        std::uint16_t m_handle_value;
        void* m_object;
        std::uint32_t m_granted_access;
    };

    struct system_handle_information_t {
        std::uint32_t         m_number_of_handles;
        system_handle_entry_t m_handles[ 1 ];
    };

    struct system_handle_entry_ex_t {
        void* m_object;
        std::uint64_t m_unique_process_id;
        std::uint64_t m_handle_value;
        std::uint32_t m_granted_access;
        std::uint16_t m_creator_back_trace_index;
        std::uint16_t m_object_type_index;
        std::uint32_t m_handle_attributes;
        std::uint32_t m_reserved;
    };

    struct system_handle_information_ex_t {
        std::uint64_t            m_number_of_handles;
        std::uint64_t            m_reserved;
        system_handle_entry_ex_t m_handles[ 1 ];
    };

    struct handle_table_entry_t {
        union {
            std::uint64_t m_volatile_low_value;
            std::uint64_t m_low_value;
            struct {
                std::uint64_t m_locked : 1;
                std::uint64_t m_ref_cnt : 16;
                std::uint64_t m_attributes : 3;
                std::uint64_t m_object_pointer_bits : 44;
            };
        };
        union {
            std::uint64_t m_high_value;
            struct {
                std::uint32_t m_granted_access;
                std::uint32_t m_granted_access_index : 16;
                std::uint32_t m_creator_back_trace_index : 16;
            };
        };
    };

    struct handle_table_t {
        std::uint32_t m_next_handle_needing_pool;
        std::int32_t  m_extra_info_pages;
        std::uint64_t m_table_code;
        void* m_quota_process;
        list_entry_t  m_handle_table_list;
        std::uint32_t m_unique_process_id;
        std::uint32_t m_flags;
    };

    enum object_information_class_t : std::uint32_t {
        object_basic_information = 0,
        object_name_information = 1,
        object_type_information = 2,
        object_types_information = 3,
        object_handle_flag_information = 4,
        object_session_information = 5
    };

    struct object_header_t {
        std::int64_t m_pointer_count;
        union {
            std::int64_t m_handle_count;
            void* m_next_to_free;
        };
        std::uint64_t m_lock;
        std::uint8_t  m_type_index;
        std::uint8_t  m_trace_flags;
        std::uint8_t  m_info_mask;
        std::uint8_t  m_flags;
        union {
            void* m_object_create_info;
            void* m_quota_block_charged;
        };
        void* m_security_descriptor;
        std::uint64_t m_body;
    };

    struct object_type_initializer_t {
        std::uint16_t m_length;
        std::uint8_t  m_object_type_flags;
        std::uint32_t m_object_type_code;
        std::uint32_t m_invalid_attributes;
        std::uint32_t m_generic_mapping[ 4 ];
        std::uint32_t m_valid_access_mask;
        std::uint32_t m_retain_access;
        std::uint32_t m_pool_type;
        std::uint32_t m_default_paged_pool_charge;
        std::uint32_t m_default_non_paged_pool_charge;
        void* m_dump_procedure;
        void* m_open_procedure;
        void* m_close_procedure;
        void* m_delete_procedure;
        void* m_parse_procedure;
        void* m_security_procedure;
        void* m_query_name_procedure;
        void* m_okay_to_close_procedure;
        std::uint32_t m_wait_object_flag_mask;
        std::uint16_t m_wait_object_flag_offset;
        std::uint16_t m_wait_object_pointer_offset;
    };

    struct object_type_t {
        list_entry_t              m_type_list;
        unicode_string_t          m_name;
        void* m_default_object;
        std::uint8_t              m_index;
        std::uint32_t             m_total_number_of_objects;
        std::uint32_t             m_total_number_of_handles;
        std::uint32_t             m_high_water_number_of_objects;
        std::uint32_t             m_high_water_number_of_handles;
        object_type_initializer_t m_type_info;
        std::uint32_t             m_type_lock[ 2 ];
        std::uint32_t             m_key;
        list_entry_t              m_callback_list;
    };

    struct dispatcher_header_t {
        union {
            std::uint32_t m_lock;
            std::int32_t  m_lock_no_new_thread;
        };
        std::int32_t m_signal_state;
        list_entry_t m_wait_list_head;
    };

    struct kevent_t {
        dispatcher_header_t m_header;
    };

    struct ksemaphore_t {
        dispatcher_header_t m_header;
        std::int32_t        m_limit;
    };

    struct kmutex_t {
        dispatcher_header_t m_header;
        list_entry_t        m_mutant_list_entry;
        void* m_owner_thread;
        std::uint8_t        m_abandoned;
        std::uint8_t        m_apc_disable;
    };

    struct kdpc_t {
        union {
            std::uint32_t m_target_info_as_ulong;
            struct {
                std::uint8_t  m_type;
                std::uint8_t  m_importance;
                std::uint16_t m_number;
            };
        };
        single_list_entry_t m_dpc_list_entry;
        std::uint64_t       m_processor_history;
        void* m_deferred_routine;
        void* m_deferred_context;
        void* m_system_argument1;
        void* m_system_argument2;
        void* m_dpc_data;
    };

    struct ktimer_t {
        dispatcher_header_t m_header;
        ularge_integer_t    m_due_time;
        list_entry_t        m_timer_list_entry;
        kdpc_t* m_dpc;
        std::uint16_t       m_processor;
        std::uint16_t       m_timer_type;
        std::int32_t        m_period;
    };

    struct ex_push_lock_t {
        union {
            struct {
                std::uint64_t m_locked : 1;
                std::uint64_t m_waiting : 1;
                std::uint64_t m_waking : 1;
                std::uint64_t m_multiple_shared : 1;
                std::uint64_t m_shared : 60;
            };
            std::uint64_t m_value;
            void* m_ptr;
        };
    };

    struct fast_mutex_t {
        std::int32_t  m_count;
        void* m_owner;
        std::uint32_t m_contention;
        kevent_t      m_event;
        std::uint32_t m_old_irql;
    };

    struct eresource_t {
        list_entry_t  m_system_resources_list;
        void* m_owner_table;
        std::int16_t  m_active_count;
        std::uint16_t m_flag;
        void* m_shared_waiters;
        void* m_exclusive_waiters;
        std::uint64_t m_owner_thread;
        std::uint32_t m_active_entries;
        std::uint32_t m_contention_count;
        std::uint32_t m_number_of_shared_waiters;
        std::uint32_t m_number_of_exclusive_waiters;
        void* m_address;
        std::uint64_t m_spin_lock;
    };

    struct driver_extension_t;

    struct driver_object_t {
        std::int16_t        m_type;
        std::int16_t        m_size;
        void* m_device_object;
        std::uint32_t       m_flags;
        void* m_driver_start;
        std::uint32_t       m_driver_size;
        void* m_driver_section;
        driver_extension_t* m_driver_extension;
        unicode_string_t    m_driver_name;
        unicode_string_t* m_hardware_database;
        void* m_fast_io_dispatch;
        void* m_driver_init;
        void* m_driver_start_io;
        void* m_driver_unload;
        void* m_major_function[ 28 ];
    };

    struct device_object_t {
        std::int16_t     m_type;
        std::uint16_t    m_size;
        std::int32_t     m_reference_count;
        driver_object_t* m_driver_object;
        void* m_next_device;
        void* m_attached_device;
        void* m_current_irp;
        void* m_timer;
        std::uint32_t    m_flags;
        std::uint32_t    m_characteristics;
        void* m_vpb;
        void* m_device_extension;
        std::uint32_t    m_device_type;
        std::int8_t      m_stack_size;
    };

    struct driver_extension_t {
        driver_object_t* m_driver_object;
        void* m_add_device;
        std::uint32_t    m_count;
        unicode_string_t m_service_key_name;
    };

    struct io_stack_location_t {
        std::uint8_t  m_major_function;
        std::uint8_t  m_minor_function;
        std::uint8_t  m_flags;
        std::uint8_t  m_control;
        std::uint64_t m_parameters[ 4 ];
        void* m_device_object;
        void* m_file_object;
        void* m_completion_routine;
        void* m_context;
    };

    struct irp_t {
        std::int16_t         m_type;
        std::uint16_t        m_size;
        void* m_mdl_address;
        std::uint32_t        m_flags;
        void* m_associated_irp;
        list_entry_t         m_thread_list_entry;
        io_status_block_t    m_io_status;
        std::uint8_t         m_requestor_mode;
        std::uint8_t         m_pending_returned;
        std::int8_t          m_stack_count;
        std::int8_t          m_current_location;
        std::uint8_t         m_cancel;
        std::uint8_t         m_cancel_irql;
        std::uint8_t         m_apc_environment;
        std::uint8_t         m_allocation_flags;
        io_status_block_t* m_user_iosb;
        kevent_t* m_user_event;
        void* m_cancel_routine;
        void* m_user_buffer;
    };

    struct peb_ldr_data_t {
        std::uint32_t m_length;
        std::uint8_t  m_initialized;
        void* m_ss_handle;
        list_entry_t  m_in_load_order_module_list;
        list_entry_t  m_in_memory_order_module_list;
        list_entry_t  m_in_initialization_order_module_list;
    };

    struct ldr_data_table_entry_t {
        list_entry_t     m_in_load_order_links;
        list_entry_t     m_in_memory_order_links;
        list_entry_t     m_in_initialization_order_links;
        void* m_dll_base;
        void* m_entry_point;
        std::uint32_t    m_size_of_image;
        unicode_string_t m_full_dll_name;
        unicode_string_t m_base_dll_name;
        std::uint32_t    m_flags;
        std::uint16_t    m_load_count;
        std::uint16_t    m_tls_index;
        list_entry_t     m_hash_links;
        std::uint32_t    m_time_date_stamp;
    };

    struct peb_t {
        std::uint8_t    m_inherited_address_space;
        std::uint8_t    m_read_image_file_exec_options;
        std::uint8_t    m_being_debugged;
        std::uint8_t    m_bit_field;
        void* m_mutant;
        void* m_image_base_address;
        peb_ldr_data_t* m_ldr;
        void* m_process_parameters;
        void* m_sub_system_data;
        void* m_process_heap;
        void* m_fast_peb_lock;
        void* m_atl_thunk_slist_ptr;
        void* m_ifeo_key;
        std::uint32_t   m_cross_process_flags;
        void* m_kernel_callback_table;
        std::uint32_t   m_system_reserved;
        std::uint32_t   m_atl_thunk_slist_ptr_32;
        void* m_api_set_map;
        std::uint32_t   m_tls_expansion_counter;
        void* m_tls_bitmap;
        std::uint32_t   m_tls_bitmap_bits[ 2 ];
        void* m_read_only_shared_memory_base;
        void* m_shared_data;
        void** m_read_only_static_server_data;
        void* m_ansi_code_page_data;
        void* m_oem_code_page_data;
        void* m_unicode_case_table_data;
        std::uint32_t   m_number_of_processors;
        std::uint32_t   m_nt_global_flag;
    };

    struct teb_t {
        std::uint8_t  m_nt_tib[ 0x38 ];
        void* m_environment_pointer;
        client_id_t   m_client_id;
        void* m_active_rpc_handle;
        void* m_thread_local_storage_pointer;
        peb_t* m_process_environment_block;
        std::uint32_t m_last_error_value;
    };

    struct m128a_ctx_t {
        std::uint64_t m_low;
        std::int64_t  m_high;
    };

    struct xmm_save_area_t {
        std::uint16_t m_control_word;
        std::uint16_t m_status_word;
        std::uint8_t  m_tag_word;
        std::uint8_t  m_reserved_1;
        std::uint16_t m_error_opcode;
        std::uint32_t m_error_offset;
        std::uint16_t m_error_selector;
        std::uint16_t m_reserved_2;
        std::uint32_t m_data_offset;
        std::uint16_t m_data_selector;
        std::uint16_t m_reserved_3;
        std::uint32_t m_mx_csr;
        std::uint32_t m_mx_csr_mask;
        m128a_ctx_t   m_float_registers[ 8 ];
        m128a_ctx_t   m_xmm_registers[ 16 ];
        std::uint8_t  m_reserved_4[ 96 ];
    };

    struct context_t {
        std::uint64_t   m_p1_home;
        std::uint64_t   m_p2_home;
        std::uint64_t   m_p3_home;
        std::uint64_t   m_p4_home;
        std::uint64_t   m_p5_home;
        std::uint64_t   m_p6_home;
        std::uint32_t   m_context_flags;
        std::uint32_t   m_mx_csr;
        std::uint16_t   m_seg_cs;
        std::uint16_t   m_seg_ds;
        std::uint16_t   m_seg_es;
        std::uint16_t   m_seg_fs;
        std::uint16_t   m_seg_gs;
        std::uint16_t   m_seg_ss;
        std::uint32_t   m_e_flags;
        std::uint64_t   m_dr0;
        std::uint64_t   m_dr1;
        std::uint64_t   m_dr2;
        std::uint64_t   m_dr3;
        std::uint64_t   m_dr6;
        std::uint64_t   m_dr7;
        std::uint64_t   m_rax;
        std::uint64_t   m_rcx;
        std::uint64_t   m_rdx;
        std::uint64_t   m_rbx;
        std::uint64_t   m_rsp;
        std::uint64_t   m_rbp;
        std::uint64_t   m_rsi;
        std::uint64_t   m_rdi;
        std::uint64_t   m_r8;
        std::uint64_t   m_r9;
        std::uint64_t   m_r10;
        std::uint64_t   m_r11;
        std::uint64_t   m_r12;
        std::uint64_t   m_r13;
        std::uint64_t   m_r14;
        std::uint64_t   m_r15;
        std::uint64_t   m_rip;
        xmm_save_area_t m_xmm_save_area;
        m128a_ctx_t     m_vector_register[ 26 ];
        std::uint64_t   m_vector_control;
        std::uint64_t   m_debug_control;
        std::uint64_t   m_last_branch_to_rip;
        std::uint64_t   m_last_branch_from_rip;
        std::uint64_t   m_last_exception_to_rip;
        std::uint64_t   m_last_exception_from_rip;
    };

    struct ktrap_frame_t {
        std::uint64_t m_p1_home;
        std::uint64_t m_p2_home;
        std::uint64_t m_p3_home;
        std::uint64_t m_p4_home;
        std::uint64_t m_p5;
        std::uint8_t  m_previous_mode;
        std::uint8_t  m_previous_irql;
        std::uint8_t  m_fault_indicator;
        std::uint8_t  m_exception_active;
        std::uint32_t m_mx_csr;
        std::uint64_t m_rax;
        std::uint64_t m_rcx;
        std::uint64_t m_rdx;
        std::uint64_t m_r8;
        std::uint64_t m_r9;
        std::uint64_t m_r10;
        std::uint64_t m_r11;
        std::uint64_t m_gs_base;
        std::uint8_t  m_xmm_pad[ 0xA0 ];
        std::uint64_t m_fault_address;
        std::uint64_t m_dr0;
        std::uint64_t m_dr1;
        std::uint64_t m_dr2;
        std::uint64_t m_dr3;
        std::uint64_t m_dr6;
        std::uint64_t m_dr7;
        std::uint64_t m_debug_control;
        std::uint64_t m_last_branch_to_rip;
        std::uint64_t m_last_branch_from_rip;
        std::uint64_t m_last_exception_to_rip;
        std::uint64_t m_last_exception_from_rip;
        std::uint16_t m_seg_ds;
        std::uint16_t m_seg_es;
        std::uint16_t m_seg_fs;
        std::uint16_t m_seg_gs;
        std::uint64_t m_trap_frame;
        std::uint64_t m_rbx;
        std::uint64_t m_rdi;
        std::uint64_t m_rsi;
        std::uint64_t m_rbp;
        std::uint64_t m_error_code;
        std::uint64_t m_rip;
        std::uint16_t m_seg_cs;
        std::uint8_t  m_fill_0;
        std::uint8_t  m_logging;
        std::uint16_t m_fill_1[ 2 ];
        std::uint32_t m_e_flags;
        std::uint32_t m_fill_2;
        std::uint64_t m_rsp;
        std::uint16_t m_seg_ss;
        std::uint16_t m_fill_3;
        std::uint32_t m_fill_4;
    };

    enum kthread_state_t : std::uint8_t {
        thread_initialized = 0,
        thread_ready = 1,
        thread_running = 2,
        thread_standby = 3,
        thread_terminated = 4,
        thread_waiting = 5,
        thread_transition = 6,
        thread_deferred_ready = 7,
        thread_gate_wait = 8
    };

    struct mdl_t {
        mdl_t* m_next;
        std::int16_t  m_size;
        std::int16_t  m_mdl_flags;
        std::uint32_t m_alloc_processor;
        void* m_process;
        void* m_mapped_system_va;
        void* m_start_va;
        std::uint32_t m_byte_count;
        std::uint32_t m_byte_offset;
    };

    struct mm_copy_address_t {
        union {
            void* m_virtual_address;
            large_integer_t m_physical_address;
        };
    };

    struct key_value_partial_information_t {
        std::uint32_t m_title_index;
        std::uint32_t m_type;
        std::uint32_t m_data_length;
        std::uint8_t  m_data[ 1 ];
    };

    struct key_value_full_information_t {
        std::uint32_t    m_title_index;
        std::uint32_t    m_type;
        std::uint32_t    m_data_offset;
        std::uint32_t    m_data_length;
        std::uint32_t    m_name_length;
        std::wchar_alias m_name[ 1 ];
    };

    struct file_basic_information_t {
        large_integer_t m_creation_time;
        large_integer_t m_last_access_time;
        large_integer_t m_last_write_time;
        large_integer_t m_change_time;
        std::uint32_t   m_file_attributes;
    };

    struct file_standard_information_t {
        large_integer_t m_allocation_size;
        large_integer_t m_end_of_file;
        std::uint32_t   m_number_of_links;
        std::uint8_t    m_delete_pending;
        std::uint8_t    m_directory;
    };

    struct file_position_information_t {
        large_integer_t m_current_byte_offset;
    };

    struct file_end_of_file_information_t {
        large_integer_t m_end_of_file;
    };

    struct sid_identifier_authority_t {
        std::uint8_t m_value[ 6 ];
    };

    struct sid_t {
        std::uint8_t               m_revision;
        std::uint8_t               m_sub_authority_count;
        sid_identifier_authority_t m_identifier_authority;
        std::uint32_t              m_sub_authority[ 1 ];
    };

    struct security_descriptor_t {
        std::uint8_t  m_revision;
        std::uint8_t  m_sbz1;
        std::uint16_t m_control;
        sid_t* m_owner;
        sid_t* m_group;
        void* m_sacl;
        void* m_dacl;
    };

    struct luid_t {
        std::uint32_t m_low_part;
        std::int32_t  m_high_part;
    };

    struct luid_and_attributes_t {
        luid_t        m_luid;
        std::uint32_t m_attributes;
    };

    struct sid_and_attributes_t {
        sid_t* m_sid;
        std::uint32_t m_attributes;
    };

    struct token_privileges_t {
        std::uint32_t         m_privilege_count;
        luid_and_attributes_t m_privileges[ 1 ];
    };

    struct rtl_osversioninfo_ex_w_t {
        std::uint32_t    m_os_version_info_size;
        std::uint32_t    m_major_version;
        std::uint32_t    m_minor_version;
        std::uint32_t    m_build_number;
        std::uint32_t    m_platform_id;
        std::wchar_alias m_csd_version[ 128 ];
        std::uint16_t    m_service_pack_major;
        std::uint16_t    m_service_pack_minor;
        std::uint16_t    m_suite_mask;
        std::uint8_t     m_product_type;
        std::uint8_t     m_reserved;
    };

    struct wnf_state_name_t {
        std::uint32_t m_data[ 2 ];
    };

    using wnf_user_callback_t = std::int32_t( __stdcall* )(
        void* wnf_subscription,
        const wnf_state_name_t* state_name,
        std::uint32_t            change_stamp,
        void* type_id,
        void* callback_context,
        void* buffer,
        std::uint32_t            buffer_size );

    __forceinline void init_list_head( list_entry_t* head ) noexcept {
        head->m_flink = head;
        head->m_blink = head;
    }

    __forceinline bool is_list_empty( const list_entry_t* head ) noexcept {
        return head->m_flink == head;
    }

    __forceinline bool remove_entry_list( list_entry_t* entry ) noexcept {
        list_entry_t* blink = entry->m_blink;
        list_entry_t* flink = entry->m_flink;
        blink->m_flink = flink;
        flink->m_blink = blink;
        return flink == blink;
    }

    __forceinline list_entry_t* remove_head_list( list_entry_t* head ) noexcept {
        list_entry_t* entry = head->m_flink;
        list_entry_t* flink = entry->m_flink;
        head->m_flink = flink;
        flink->m_blink = head;
        return entry;
    }

    __forceinline list_entry_t* remove_tail_list( list_entry_t* head ) noexcept {
        list_entry_t* entry = head->m_blink;
        list_entry_t* blink = entry->m_blink;
        head->m_blink = blink;
        blink->m_flink = head;
        return entry;
    }

    __forceinline void insert_head_list( list_entry_t* head, list_entry_t* entry ) noexcept {
        list_entry_t* flink = head->m_flink;
        entry->m_flink = flink;
        entry->m_blink = head;
        flink->m_blink = entry;
        head->m_flink = entry;
    }

    __forceinline void insert_tail_list( list_entry_t* head, list_entry_t* entry ) noexcept {
        list_entry_t* blink = head->m_blink;
        entry->m_flink = head;
        entry->m_blink = blink;
        blink->m_flink = entry;
        head->m_blink = entry;
    }

} // namespace nt