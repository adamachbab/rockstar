#pragma once

namespace nt {

    using ntstatus_t = std::int32_t;

    constexpr std::uint32_t severity_success = 0x0;
    constexpr std::uint32_t severity_informational = 0x1;
    constexpr std::uint32_t severity_warning = 0x2;
    constexpr std::uint32_t severity_error = 0x3;

    __forceinline constexpr std::uint32_t status_severity( ntstatus_t s ) noexcept {
        return ( static_cast< std::uint32_t >( s ) >> 30 ) & 0x3;
    }

    __forceinline constexpr std::uint32_t status_facility( ntstatus_t s ) noexcept {
        return ( static_cast< std::uint32_t >( s ) >> 16 ) & 0x0FFF;
    }

    __forceinline constexpr std::uint32_t status_code( ntstatus_t s ) noexcept {
        return static_cast< std::uint32_t >( s ) & 0xFFFF;
    }

    __forceinline constexpr bool nt_success( ntstatus_t s ) noexcept {
        return s >= 0;
    }

    __forceinline constexpr bool nt_information( ntstatus_t s ) noexcept {
        return status_severity( s ) == severity_informational;
    }

    __forceinline constexpr bool nt_warning( ntstatus_t s ) noexcept {
        return status_severity( s ) == severity_warning;
    }

    __forceinline constexpr bool nt_error( ntstatus_t s ) noexcept {
        return status_severity( s ) == severity_error;
    }

    constexpr ntstatus_t status_success = 0x00000000;
    constexpr ntstatus_t status_wait_0 = 0x00000000;
    constexpr ntstatus_t status_wait_1 = 0x00000001;
    constexpr ntstatus_t status_wait_2 = 0x00000002;
    constexpr ntstatus_t status_wait_3 = 0x00000003;
    constexpr ntstatus_t status_abandoned = 0x00000080;
    constexpr ntstatus_t status_user_apc = 0x000000C0;
    constexpr ntstatus_t status_kernel_apc = 0x00000100;
    constexpr ntstatus_t status_alerted = 0x00000101;
    constexpr ntstatus_t status_timeout = 0x00000102;
    constexpr ntstatus_t status_pending = 0x00000103;
    constexpr ntstatus_t status_reparse = 0x00000104;
    constexpr ntstatus_t status_more_entries = 0x00000105;
    constexpr ntstatus_t status_not_all_assigned = 0x00000106;
    constexpr ntstatus_t status_some_not_mapped = 0x00000107;
    constexpr ntstatus_t status_buffer_overflow = 0x80000005;
    constexpr ntstatus_t status_no_more_files = 0x80000006;
    constexpr ntstatus_t status_no_more_entries = 0x8000001A;

    constexpr ntstatus_t status_unsuccessful = 0xC0000001;
    constexpr ntstatus_t status_not_implemented = 0xC0000002;
    constexpr ntstatus_t status_invalid_info_class = 0xC0000003;
    constexpr ntstatus_t status_info_length_mismatch = 0xC0000004;
    constexpr ntstatus_t status_access_violation = 0xC0000005;
    constexpr ntstatus_t status_in_page_error = 0xC0000006;
    constexpr ntstatus_t status_invalid_handle = 0xC0000008;
    constexpr ntstatus_t status_invalid_parameter = 0xC000000D;
    constexpr ntstatus_t status_no_such_device = 0xC000000E;
    constexpr ntstatus_t status_no_such_file = 0xC000000F;
    constexpr ntstatus_t status_invalid_device_request = 0xC0000010;
    constexpr ntstatus_t status_end_of_file = 0xC0000011;
    constexpr ntstatus_t status_wrong_volume = 0xC0000012;
    constexpr ntstatus_t status_no_media_in_device = 0xC0000013;
    constexpr ntstatus_t status_no_memory = 0xC0000017;
    constexpr ntstatus_t status_conflicting_addresses = 0xC0000018;
    constexpr ntstatus_t status_not_mapped_view = 0xC0000019;
    constexpr ntstatus_t status_unable_to_free_vm = 0xC000001A;
    constexpr ntstatus_t status_unable_to_delete_section = 0xC000001B;
    constexpr ntstatus_t status_illegal_instruction = 0xC000001D;
    constexpr ntstatus_t status_already_committed = 0xC0000021;
    constexpr ntstatus_t status_access_denied = 0xC0000022;
    constexpr ntstatus_t status_buffer_too_small = 0xC0000023;
    constexpr ntstatus_t status_object_type_mismatch = 0xC0000024;
    constexpr ntstatus_t status_non_continuable_exception = 0xC0000025;
    constexpr ntstatus_t status_bad_stack = 0xC0000028;
    constexpr ntstatus_t status_object_name_invalid = 0xC0000033;
    constexpr ntstatus_t status_object_name_not_found = 0xC0000034;
    constexpr ntstatus_t status_object_name_collision = 0xC0000035;
    constexpr ntstatus_t status_object_path_invalid = 0xC0000039;
    constexpr ntstatus_t status_object_path_not_found = 0xC000003A;
    constexpr ntstatus_t status_object_path_syntax_bad = 0xC000003B;
    constexpr ntstatus_t status_data_overrun = 0xC000003C;
    constexpr ntstatus_t status_sharing_violation = 0xC0000043;
    constexpr ntstatus_t status_quota_exceeded = 0xC0000044;
    constexpr ntstatus_t status_invalid_page_protection = 0xC0000045;
    constexpr ntstatus_t status_mutant_not_owned = 0xC0000046;
    constexpr ntstatus_t status_semaphore_limit_exceeded = 0xC0000047;
    constexpr ntstatus_t status_port_already_set = 0xC0000048;
    constexpr ntstatus_t status_file_lock_conflict = 0xC0000054;
    constexpr ntstatus_t status_lock_not_granted = 0xC0000055;
    constexpr ntstatus_t status_delete_pending = 0xC0000056;
    constexpr ntstatus_t status_privilege_not_held = 0xC0000061;
    constexpr ntstatus_t status_disk_full = 0xC000007F;
    constexpr ntstatus_t status_insufficient_resources = 0xC000009A;
    constexpr ntstatus_t status_media_write_protected = 0xC00000A2;
    constexpr ntstatus_t status_device_not_ready = 0xC00000A3;
    constexpr ntstatus_t status_invalid_pipe_state = 0xC00000AD;
    constexpr ntstatus_t status_pipe_busy = 0xC00000AE;
    constexpr ntstatus_t status_pipe_disconnected = 0xC00000B0;
    constexpr ntstatus_t status_pipe_closing = 0xC00000B1;
    constexpr ntstatus_t status_pipe_connected = 0xC00000B2;
    constexpr ntstatus_t status_pipe_listening = 0xC00000B3;
    constexpr ntstatus_t status_invalid_read_mode = 0xC00000B4;
    constexpr ntstatus_t status_io_timeout = 0xC00000B5;
    constexpr ntstatus_t status_not_supported = 0xC00000BB;
    constexpr ntstatus_t status_network_unreachable = 0xC000023C;
    constexpr ntstatus_t status_internal_error = 0xC00000E5;
    constexpr ntstatus_t status_invalid_parameter_1 = 0xC00000EF;
    constexpr ntstatus_t status_invalid_parameter_2 = 0xC00000F0;
    constexpr ntstatus_t status_invalid_parameter_3 = 0xC00000F1;
    constexpr ntstatus_t status_invalid_parameter_4 = 0xC00000F2;
    constexpr ntstatus_t status_invalid_parameter_5 = 0xC00000F3;
    constexpr ntstatus_t status_process_is_terminating = 0xC000010A;
    constexpr ntstatus_t status_bad_compression_buffer = 0xC0000242;
    constexpr ntstatus_t status_not_found = 0xC0000225;
    constexpr ntstatus_t status_driver_failed_prior_unload = 0xC000026C;
    constexpr ntstatus_t status_hive_unloaded = 0xC0000425;
    constexpr ntstatus_t status_image_already_loaded = 0xC000010E;
    constexpr ntstatus_t status_not_a_directory = 0xC0000103;
    constexpr ntstatus_t status_directory_not_empty = 0xC0000101;
    constexpr ntstatus_t status_too_many_opened_files = 0xC000011F;
    constexpr ntstatus_t status_cancelled = 0xC0000120;
    constexpr ntstatus_t status_cannot_delete = 0xC0000121;

} // namespace nt