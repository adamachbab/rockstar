#pragma once

namespace nt {

    constexpr std::uint32_t obj_inherit = 0x00000002;
    constexpr std::uint32_t obj_permanent = 0x00000010;
    constexpr std::uint32_t obj_exclusive = 0x00000020;
    constexpr std::uint32_t obj_case_insensitive = 0x00000040;
    constexpr std::uint32_t obj_openif = 0x00000080;
    constexpr std::uint32_t obj_openlink = 0x00000100;
    constexpr std::uint32_t obj_kernel_handle = 0x00000200;
    constexpr std::uint32_t obj_force_access_check = 0x00000400;
    constexpr std::uint32_t obj_ignore_impersonated_devicemap = 0x00000800;
    constexpr std::uint32_t obj_dont_reparse = 0x00001000;

    constexpr std::uint32_t generic_read = 0x80000000;
    constexpr std::uint32_t generic_write = 0x40000000;
    constexpr std::uint32_t generic_execute = 0x20000000;
    constexpr std::uint32_t generic_all = 0x10000000;
    constexpr std::uint32_t maximum_allowed = 0x02000000;
    constexpr std::uint32_t access_system_security = 0x01000000;
    constexpr std::uint32_t standard_rights_required = 0x000F0000;
    constexpr std::uint32_t standard_rights_all = 0x001F0000;
    constexpr std::uint32_t standard_rights_read = 0x00020000;
    constexpr std::uint32_t standard_rights_write = 0x00020000;
    constexpr std::uint32_t standard_rights_execute = 0x00020000;
    constexpr std::uint32_t synchronize = 0x00100000;
    constexpr std::uint32_t delete_access = 0x00010000;
    constexpr std::uint32_t read_control = 0x00020000;
    constexpr std::uint32_t write_dac = 0x00040000;
    constexpr std::uint32_t write_owner = 0x00080000;

    constexpr std::uint32_t process_terminate = 0x0001;
    constexpr std::uint32_t process_create_thread = 0x0002;
    constexpr std::uint32_t process_set_sessionid = 0x0004;
    constexpr std::uint32_t process_vm_operation = 0x0008;
    constexpr std::uint32_t process_vm_read = 0x0010;
    constexpr std::uint32_t process_vm_write = 0x0020;
    constexpr std::uint32_t process_dup_handle = 0x0040;
    constexpr std::uint32_t process_create_process = 0x0080;
    constexpr std::uint32_t process_set_quota = 0x0100;
    constexpr std::uint32_t process_set_information = 0x0200;
    constexpr std::uint32_t process_query_information = 0x0400;
    constexpr std::uint32_t process_suspend_resume = 0x0800;
    constexpr std::uint32_t process_query_limited_information = 0x1000;
    constexpr std::uint32_t process_all_access = 0x001FFFFF;

    constexpr std::uint32_t thread_terminate = 0x0001;
    constexpr std::uint32_t thread_suspend_resume = 0x0002;
    constexpr std::uint32_t thread_get_context = 0x0008;
    constexpr std::uint32_t thread_set_context = 0x0010;
    constexpr std::uint32_t thread_query_information = 0x0040;
    constexpr std::uint32_t thread_set_information = 0x0020;
    constexpr std::uint32_t thread_set_thread_token = 0x0080;
    constexpr std::uint32_t thread_impersonate = 0x0100;
    constexpr std::uint32_t thread_direct_impersonation = 0x0200;
    constexpr std::uint32_t thread_query_limited_information = 0x0800;
    constexpr std::uint32_t thread_all_access = 0x001FFFFF;

    enum pool_type_t : std::uint32_t {
        non_paged_pool = 0,
        paged_pool = 1,
        non_paged_pool_must_succeed = 2,
        dont_use_this_type = 3,
        non_paged_pool_cache_aligned = 4,
        paged_pool_cache_aligned = 5,
        non_paged_pool_cache_aligned_must_s = 6,
        max_pool_type = 7,
        non_paged_pool_nx = 512,
        non_paged_pool_nx_cache_aligned = 516,
        paged_pool_session_nx = 545
    };

    enum memory_caching_type_t : std::uint32_t {
        mm_non_cached = 0,
        mm_cached = 1,
        mm_write_combined = 2,
        mm_hardware_coherent = 3,
        mm_non_cached_unordered = 4,
        mm_us_wc_cached = 5,
        mm_maximum_cache_type = 6
    };

    constexpr std::uint32_t page_no_access = 0x001;
    constexpr std::uint32_t page_read_only = 0x002;
    constexpr std::uint32_t page_read_write = 0x004;
    constexpr std::uint32_t page_write_copy = 0x008;
    constexpr std::uint32_t page_execute = 0x010;
    constexpr std::uint32_t page_execute_read = 0x020;
    constexpr std::uint32_t page_execute_read_write = 0x040;
    constexpr std::uint32_t page_execute_write_copy = 0x080;
    constexpr std::uint32_t page_guard = 0x100;
    constexpr std::uint32_t page_no_cache = 0x200;
    constexpr std::uint32_t page_write_combine = 0x400;

    constexpr std::uint32_t mem_commit = 0x00001000;
    constexpr std::uint32_t mem_reserve = 0x00002000;
    constexpr std::uint32_t mem_decommit = 0x00004000;
    constexpr std::uint32_t mem_release = 0x00008000;
    constexpr std::uint32_t mem_reset = 0x00080000;
    constexpr std::uint32_t mem_top_down = 0x00100000;
    constexpr std::uint32_t mem_write_watch = 0x00200000;
    constexpr std::uint32_t mem_physical = 0x00400000;
    constexpr std::uint32_t mem_large_pages = 0x20000000;

    constexpr std::uint32_t file_attribute_readonly = 0x00000001;
    constexpr std::uint32_t file_attribute_hidden = 0x00000002;
    constexpr std::uint32_t file_attribute_system = 0x00000004;
    constexpr std::uint32_t file_attribute_directory = 0x00000010;
    constexpr std::uint32_t file_attribute_archive = 0x00000020;
    constexpr std::uint32_t file_attribute_device = 0x00000040;
    constexpr std::uint32_t file_attribute_normal = 0x00000080;
    constexpr std::uint32_t file_attribute_temporary = 0x00000100;
    constexpr std::uint32_t file_attribute_sparse_file = 0x00000200;
    constexpr std::uint32_t file_attribute_reparse_point = 0x00000400;
    constexpr std::uint32_t file_attribute_compressed = 0x00000800;
    constexpr std::uint32_t file_attribute_offline = 0x00001000;
    constexpr std::uint32_t file_attribute_not_content_indexed = 0x00002000;
    constexpr std::uint32_t file_attribute_encrypted = 0x00004000;

    constexpr std::uint32_t file_share_read = 0x00000001;
    constexpr std::uint32_t file_share_write = 0x00000002;
    constexpr std::uint32_t file_share_delete = 0x00000004;

    enum file_create_disposition_t : std::uint32_t {
        file_supersede = 0,
        file_open = 1,
        file_create = 2,
        file_open_if = 3,
        file_overwrite = 4,
        file_overwrite_if = 5,
        file_maximum_disposition = 5
    };

    constexpr std::uint32_t file_directory_file = 0x00000001;
    constexpr std::uint32_t file_write_through = 0x00000002;
    constexpr std::uint32_t file_sequential_only = 0x00000004;
    constexpr std::uint32_t file_no_intermediate_buffering = 0x00000008;
    constexpr std::uint32_t file_synchronous_io_alert = 0x00000010;
    constexpr std::uint32_t file_synchronous_io_nonalert = 0x00000020;
    constexpr std::uint32_t file_non_directory_file = 0x00000040;
    constexpr std::uint32_t file_create_tree_connection = 0x00000080;
    constexpr std::uint32_t file_complete_if_oplocked = 0x00000100;
    constexpr std::uint32_t file_no_ea_knowledge = 0x00000200;
    constexpr std::uint32_t file_open_remote_instance = 0x00000400;
    constexpr std::uint32_t file_random_access = 0x00000800;
    constexpr std::uint32_t file_delete_on_close = 0x00001000;
    constexpr std::uint32_t file_open_by_file_id = 0x00002000;
    constexpr std::uint32_t file_open_for_backup_intent = 0x00004000;
    constexpr std::uint32_t file_no_compression = 0x00008000;
    constexpr std::uint32_t file_reserve_opfilter = 0x00100000;
    constexpr std::uint32_t file_open_reparse_point = 0x00200000;
    constexpr std::uint32_t file_open_no_recall = 0x00400000;

    enum file_information_class_t : std::uint32_t {
        file_directory_information = 1,
        file_full_directory_information = 2,
        file_both_directory_information = 3,
        file_basic_information = 4,
        file_standard_information = 5,
        file_internal_information = 6,
        file_ea_information = 7,
        file_access_information = 8,
        file_name_information = 9,
        file_rename_information = 10,
        file_link_information = 11,
        file_disposition_information = 13,
        file_position_information = 14,
        file_all_information = 18,
        file_end_of_file_information = 20,
        file_allocation_information = 19,
        file_pipe_information = 23,
        file_pipe_local_information = 24,
        file_pipe_remote_information = 25,
        file_stream_information = 22,
        file_network_open_information = 34
    };

    constexpr std::uint32_t reg_none = 0;
    constexpr std::uint32_t reg_sz = 1;
    constexpr std::uint32_t reg_expand_sz = 2;
    constexpr std::uint32_t reg_binary = 3;
    constexpr std::uint32_t reg_dword = 4;
    constexpr std::uint32_t reg_dword_big_endian = 5;
    constexpr std::uint32_t reg_link = 6;
    constexpr std::uint32_t reg_multi_sz = 7;
    constexpr std::uint32_t reg_resource_list = 8;
    constexpr std::uint32_t reg_full_resource_descriptor = 9;
    constexpr std::uint32_t reg_resource_requirements_list = 10;
    constexpr std::uint32_t reg_qword = 11;

    constexpr std::uint32_t key_query_value = 0x0001;
    constexpr std::uint32_t key_set_value = 0x0002;
    constexpr std::uint32_t key_create_sub_key = 0x0004;
    constexpr std::uint32_t key_enumerate_sub_keys = 0x0008;
    constexpr std::uint32_t key_notify = 0x0010;
    constexpr std::uint32_t key_create_link = 0x0020;
    constexpr std::uint32_t key_all_access = 0x000F003F;

    enum key_information_class_t : std::uint32_t {
        key_basic_information = 0,
        key_node_information = 1,
        key_full_information = 2,
        key_name_information = 3,
        key_cached_information = 4,
        key_flags_information = 5,
        key_virtualization_information = 6,
        key_handle_tags_information = 7
    };

    enum key_value_information_class_t : std::uint32_t {
        key_value_basic_information = 0,
        key_value_full_information = 1,
        key_value_partial_information = 2,
        key_value_full_information_align_64 = 3,
        key_value_partial_information_align_64 = 4
    };

    enum system_information_class_t : std::uint32_t {
        system_basic_information = 0,
        system_processor_information = 1,
        system_performance_information = 2,
        system_time_of_day_information = 3,
        system_path_information = 4,
        system_process_information = 5,
        system_call_count_information = 6,
        system_device_information = 7,
        system_processor_performance_info = 8,
        system_module_information = 11,
        system_handle_information = 16,
        system_object_information = 17,
        system_kernel_debugger_information = 35,
        system_extended_handle_information = 64,
        system_big_pool_information = 66,
        system_boot_environment_information = 90,
        system_codeintegrity_information = 103,
        system_kernel_va_shadow_information = 196
    };

    constexpr std::uint8_t passive_level = 0;
    constexpr std::uint8_t apc_level = 1;
    constexpr std::uint8_t dispatch_level = 2;
    constexpr std::uint8_t cmci_level = 5;
    constexpr std::uint8_t device_level_min = 3;
    constexpr std::uint8_t device_level_max = 12;
    constexpr std::uint8_t profile_level = 27;
    constexpr std::uint8_t clock_level = 28;
    constexpr std::uint8_t ipi_level = 29;
    constexpr std::uint8_t power_level = 30;
    constexpr std::uint8_t high_level = 31;

    constexpr std::uint8_t kernel_mode = 0;
    constexpr std::uint8_t user_mode = 1;

    enum wait_reason_t : std::uint32_t {
        wait_executive = 0,
        wait_free_page = 1,
        wait_page_in = 2,
        wait_pool_allocation = 3,
        wait_delay_execution = 4,
        wait_suspended = 5,
        wait_user_request = 6,
        wait_wr_queue = 7,
        wait_wr_lpc_receive = 8,
        wait_wr_lpc_reply = 9,
        wait_wr_virtual_memory = 10,
        wait_wr_page_out = 11,
        wait_wr_rendezvous = 12,
        wait_wr_keyed_event = 13,
        wait_wr_terminated = 14,
        wait_wr_process_in_swap = 15,
        wait_wr_cpu_rate_control = 16,
        wait_wr_calloutstack = 17,
        wait_wr_kernel = 18,
        wait_wr_resource = 19,
        wait_wr_push_lock = 20,
        wait_wr_mutex = 21,
        wait_wr_quantum_end = 22,
        wait_wr_dispatch_int = 23,
        wait_wr_preempted = 24,
        wait_wr_yield_execution = 25,
        wait_maximum_reason = 26
    };

    constexpr std::uint32_t mdl_mapped_to_system_va = 0x0001;
    constexpr std::uint32_t mdl_pages_locked = 0x0002;
    constexpr std::uint32_t mdl_source_is_nonpaged_pool = 0x0004;
    constexpr std::uint32_t mdl_allocated_fixed_size = 0x0008;
    constexpr std::uint32_t mdl_partial = 0x0010;
    constexpr std::uint32_t mdl_partial_has_been_mapped = 0x0020;
    constexpr std::uint32_t mdl_io_page_read = 0x0040;
    constexpr std::uint32_t mdl_write_operation = 0x0080;
    constexpr std::uint32_t mdl_parent_mapped_system_va = 0x0100;
    constexpr std::uint32_t mdl_free_extra_ptes = 0x0200;
    constexpr std::uint32_t mdl_describes_awe = 0x0400;
    constexpr std::uint32_t mdl_io_space = 0x0800;
    constexpr std::uint32_t mdl_network_header = 0x1000;
    constexpr std::uint32_t mdl_mapping_can_fail = 0x2000;
    constexpr std::uint32_t mdl_allocated_must_succeed = 0x4000;

    constexpr std::uint32_t vad_type_dll_data = 0;
    constexpr std::uint32_t vad_type_dll_image = 1;
    constexpr std::uint32_t vad_type_shared_data = 2;
    constexpr std::uint32_t vad_type_awe = 3;
    constexpr std::uint32_t vad_type_write_watch = 4;
    constexpr std::uint32_t vad_type_large_pages = 5;
    constexpr std::uint32_t vad_type_rotate_physical = 6;
    constexpr std::uint32_t vad_type_devicephysical = 7;

    constexpr std::uint8_t pfn_zero_page = 0;
    constexpr std::uint8_t pfn_free_page = 1;
    constexpr std::uint8_t pfn_standby_page = 2;
    constexpr std::uint8_t pfn_modified_page = 3;
    constexpr std::uint8_t pfn_modified_norite = 4;
    constexpr std::uint8_t pfn_bad_page = 5;
    constexpr std::uint8_t pfn_active_and_valid = 6;
    constexpr std::uint8_t pfn_transition_page = 7;

    constexpr std::uint64_t page_size_4kb = 0x1000;
    constexpr std::uint64_t page_size_2mb = 0x200000;
    constexpr std::uint64_t page_size_1gb = 0x40000000;
    constexpr std::uint64_t page_mask_4kb = 0x0FFF;
    constexpr std::uint64_t page_mask_2mb = 0x1FFFFF;
    constexpr std::uint64_t page_mask_1gb = 0x3FFFFFFF;
    constexpr std::uint32_t page_shift = 12;

    constexpr std::uint16_t subsystem_unknown = 0;
    constexpr std::uint16_t subsystem_native = 1;
    constexpr std::uint16_t subsystem_windows_gui = 2;
    constexpr std::uint16_t subsystem_windows_cui = 3;
    constexpr std::uint16_t subsystem_os2_cui = 5;
    constexpr std::uint16_t subsystem_posix_cui = 7;
    constexpr std::uint16_t subsystem_windows_ce_gui = 9;
    constexpr std::uint16_t subsystem_efi_application = 10;
    constexpr std::uint16_t subsystem_efi_boot_driver = 11;
    constexpr std::uint16_t subsystem_efi_runtime_driver = 12;
    constexpr std::uint16_t subsystem_efi_rom = 13;
    constexpr std::uint16_t subsystem_xbox = 14;

    __forceinline constexpr std::uint64_t page_align_down( std::uint64_t addr ) noexcept {
        return addr & ~page_mask_4kb;
    }

    __forceinline constexpr std::uint64_t page_align_up( std::uint64_t addr ) noexcept {
        return ( addr + page_mask_4kb ) & ~page_mask_4kb;
    }

    __forceinline constexpr std::uint64_t page_offset( std::uint64_t addr ) noexcept {
        return addr & page_mask_4kb;
    }

    __forceinline constexpr std::uint64_t bytes_to_pages( std::uint64_t bytes ) noexcept {
        return ( bytes + page_mask_4kb ) >> page_shift;
    }

} // namespace nt