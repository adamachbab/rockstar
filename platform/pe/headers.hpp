#pragma once

namespace pe {

    constexpr std::uint16_t dos_signature = 0x5A4D;
    constexpr std::uint32_t nt_signature = 0x00004550;

    constexpr std::uint16_t optional_magic_32 = 0x010B;
    constexpr std::uint16_t optional_magic_64 = 0x020B;

    constexpr std::uint16_t machine_i386 = 0x014C;
    constexpr std::uint16_t machine_amd64 = 0x8664;
    constexpr std::uint16_t machine_arm = 0x01C0;
    constexpr std::uint16_t machine_arm64 = 0xAA64;
    constexpr std::uint16_t machine_ia64 = 0x0200;

    constexpr std::uint32_t directory_entries = 16;

    enum directory_index : std::uint32_t {
        directory_export = 0,
        directory_import = 1,
        directory_resource = 2,
        directory_exception = 3,
        directory_security = 4,
        directory_basereloc = 5,
        directory_debug = 6,
        directory_architecture = 7,
        directory_globalptr = 8,
        directory_tls = 9,
        directory_load_config = 10,
        directory_bound_import = 11,
        directory_iat = 12,
        directory_delay_import = 13,
        directory_com_descriptor = 14,
        directory_reserved = 15
    };

    enum section_characteristics : std::uint32_t {
        section_type_no_pad = 0x00000008,
        section_cnt_code = 0x00000020,
        section_cnt_initialized_data = 0x00000040,
        section_cnt_uninitialized_data = 0x00000080,
        section_gprel = 0x00008000,
        section_align_1_bytes = 0x00100000,
        section_align_2_bytes = 0x00200000,
        section_align_4_bytes = 0x00300000,
        section_align_8_bytes = 0x00400000,
        section_align_16_bytes = 0x00500000,
        section_mem_discardable = 0x02000000,
        section_mem_not_cached = 0x04000000,
        section_mem_not_paged = 0x08000000,
        section_mem_shared = 0x10000000,
        section_mem_execute = 0x20000000,
        section_mem_read = 0x40000000,
        section_mem_write = 0x80000000
    };

    enum reloc_type : std::uint16_t {
        reloc_absolute = 0,
        reloc_high = 1,
        reloc_low = 2,
        reloc_highlow = 3,
        reloc_highadj = 4,
        reloc_mips_jmpaddr = 5,
        reloc_arm_mov32 = 5,
        reloc_riscv_high20 = 5,
        reloc_thumb_mov32 = 7,
        reloc_riscv_low12i = 7,
        reloc_dir64 = 10
    };

    enum debug_type : std::uint32_t {
        debug_type_unknown = 0,
        debug_type_coff = 1,
        debug_type_codeview = 2,
        debug_type_fpo = 3,
        debug_type_misc = 4,
        debug_type_exception = 5,
        debug_type_fixup = 6,
        debug_type_omap_to_src = 7,
        debug_type_omap_from_src = 8,
        debug_type_borland = 9,
        debug_type_reserved10 = 10,
        debug_type_clsid = 11,
        debug_type_repro = 16,
        debug_type_ex_dllcharacteristics = 20
    };

    constexpr std::uint32_t codeview_signature_rsds = 0x53445352; // 'RSDS'
    constexpr std::uint32_t codeview_signature_nb10 = 0x3031424E; // 'NB10'

#pragma pack(push, 1)

    struct data_directory_t {
        std::uint32_t m_virtual_address;
        std::uint32_t m_size;

        constexpr bool is_valid( ) const noexcept {
            return m_virtual_address != 0 && m_size != 0;
        }

        template<typename T>
        T as_rva( std::uint64_t module_base ) const noexcept {
            if ( !is_valid( ) ) return nullptr;
            return reinterpret_cast< T >( module_base + m_virtual_address );
        }
    };

    struct dos_header_t {
        std::uint16_t m_magic;
        std::uint16_t m_cblp;
        std::uint16_t m_cp;
        std::uint16_t m_crlc;
        std::uint16_t m_cparhdr;
        std::uint16_t m_minalloc;
        std::uint16_t m_maxalloc;
        std::uint16_t m_ss;
        std::uint16_t m_sp;
        std::uint16_t m_csum;
        std::uint16_t m_ip;
        std::uint16_t m_cs;
        std::uint16_t m_lfarlc;
        std::uint16_t m_ovno;
        std::uint16_t m_res[ 4 ];
        std::uint16_t m_oemid;
        std::uint16_t m_oeminfo;
        std::uint16_t m_res2[ 10 ];
        std::int32_t  m_lfanew;

        constexpr bool is_valid( ) const noexcept {
            return m_magic == dos_signature;
        }
    };

    struct file_header_t {
        std::uint16_t m_machine;
        std::uint16_t m_number_of_sections;
        std::uint32_t m_time_date_stamp;
        std::uint32_t m_pointer_to_symbol_table;
        std::uint32_t m_number_of_symbols;
        std::uint16_t m_size_of_optional_header;
        std::uint16_t m_characteristics;

        constexpr bool is_64bit( ) const noexcept {
            return m_machine == machine_amd64 || m_machine == machine_arm64;
        }
    };

    struct optional_header_64_t {
        std::uint16_t    m_magic;
        std::uint8_t     m_major_linker_version;
        std::uint8_t     m_minor_linker_version;
        std::uint32_t    m_size_of_code;
        std::uint32_t    m_size_of_initialized_data;
        std::uint32_t    m_size_of_uninitialized_data;
        std::uint32_t    m_address_of_entry_point;
        std::uint32_t    m_base_of_code;
        std::uint64_t    m_image_base;
        std::uint32_t    m_section_alignment;
        std::uint32_t    m_file_alignment;
        std::uint16_t    m_major_os_version;
        std::uint16_t    m_minor_os_version;
        std::uint16_t    m_major_image_version;
        std::uint16_t    m_minor_image_version;
        std::uint16_t    m_major_subsystem_version;
        std::uint16_t    m_minor_subsystem_version;
        std::uint32_t    m_win32_version_value;
        std::uint32_t    m_size_of_image;
        std::uint32_t    m_size_of_headers;
        std::uint32_t    m_check_sum;
        std::uint16_t    m_subsystem;
        std::uint16_t    m_dll_characteristics;
        std::uint64_t    m_size_of_stack_reserve;
        std::uint64_t    m_size_of_stack_commit;
        std::uint64_t    m_size_of_heap_reserve;
        std::uint64_t    m_size_of_heap_commit;
        std::uint32_t    m_loader_flags;
        std::uint32_t    m_number_of_rva_and_sizes;
        data_directory_t m_data_directory[ directory_entries ];

        constexpr bool is_valid( ) const noexcept {
            return m_magic == optional_magic_64;
        }
    };

    struct optional_header_32_t {
        std::uint16_t    m_magic;
        std::uint8_t     m_major_linker_version;
        std::uint8_t     m_minor_linker_version;
        std::uint32_t    m_size_of_code;
        std::uint32_t    m_size_of_initialized_data;
        std::uint32_t    m_size_of_uninitialized_data;
        std::uint32_t    m_address_of_entry_point;
        std::uint32_t    m_base_of_code;
        std::uint32_t    m_base_of_data;
        std::uint32_t    m_image_base;
        std::uint32_t    m_section_alignment;
        std::uint32_t    m_file_alignment;
        std::uint16_t    m_major_os_version;
        std::uint16_t    m_minor_os_version;
        std::uint16_t    m_major_image_version;
        std::uint16_t    m_minor_image_version;
        std::uint16_t    m_major_subsystem_version;
        std::uint16_t    m_minor_subsystem_version;
        std::uint32_t    m_win32_version_value;
        std::uint32_t    m_size_of_image;
        std::uint32_t    m_size_of_headers;
        std::uint32_t    m_check_sum;
        std::uint16_t    m_subsystem;
        std::uint16_t    m_dll_characteristics;
        std::uint32_t    m_size_of_stack_reserve;
        std::uint32_t    m_size_of_stack_commit;
        std::uint32_t    m_size_of_heap_reserve;
        std::uint32_t    m_size_of_heap_commit;
        std::uint32_t    m_loader_flags;
        std::uint32_t    m_number_of_rva_and_sizes;
        data_directory_t m_data_directory[ directory_entries ];

        constexpr bool is_valid( ) const noexcept {
            return m_magic == optional_magic_32;
        }
    };

    struct nt_headers_t {
        std::uint32_t        m_signature;
        file_header_t        m_file_header;
        optional_header_64_t m_optional_header;

        constexpr bool is_valid( ) const noexcept {
            return m_signature == nt_signature && m_optional_header.is_valid( );
        }

        constexpr std::uint16_t m_number_of_sections( ) const noexcept {
            return m_file_header.m_number_of_sections;
        }

        constexpr std::uint16_t m_size_of_optional_header( ) const noexcept {
            return m_file_header.m_size_of_optional_header;
        }

        constexpr const data_directory_t& m_export_table( )      const noexcept { return m_optional_header.m_data_directory[ directory_export ]; }
        constexpr const data_directory_t& m_import_table( )      const noexcept { return m_optional_header.m_data_directory[ directory_import ]; }
        constexpr const data_directory_t& m_resource_table( )    const noexcept { return m_optional_header.m_data_directory[ directory_resource ]; }
        constexpr const data_directory_t& m_exception_table( )   const noexcept { return m_optional_header.m_data_directory[ directory_exception ]; }
        constexpr const data_directory_t& m_basereloc_table( )   const noexcept { return m_optional_header.m_data_directory[ directory_basereloc ]; }
        constexpr const data_directory_t& m_debug_table( )       const noexcept { return m_optional_header.m_data_directory[ directory_debug ]; }
        constexpr const data_directory_t& m_tls_table( )         const noexcept { return m_optional_header.m_data_directory[ directory_tls ]; }
        constexpr const data_directory_t& m_load_config_table( ) const noexcept { return m_optional_header.m_data_directory[ directory_load_config ]; }
        constexpr const data_directory_t& m_iat_table( )         const noexcept { return m_optional_header.m_data_directory[ directory_iat ]; }
        constexpr const data_directory_t& m_delay_import_table( ) const noexcept { return m_optional_header.m_data_directory[ directory_delay_import ]; }
    };

    struct nt_headers_32_t {
        std::uint32_t        m_signature;
        file_header_t        m_file_header;
        optional_header_32_t m_optional_header;

        constexpr bool is_valid( ) const noexcept {
            return m_signature == nt_signature && m_optional_header.is_valid( );
        }
    };

    struct section_header_t {
        char m_name[ 8 ];
        union {
            std::uint32_t m_physical_address;
            std::uint32_t m_virtual_size;
        };
        std::uint32_t m_virtual_address;
        std::uint32_t m_size_of_raw_data;
        std::uint32_t m_pointer_to_raw_data;
        std::uint32_t m_pointer_to_relocations;
        std::uint32_t m_pointer_to_linenumbers;
        std::uint16_t m_number_of_relocations;
        std::uint16_t m_number_of_linenumbers;
        std::uint32_t m_characteristics;

        bool is_named( const char* name ) const noexcept {
            for ( std::size_t i = 0; i < 8; ++i ) {
                if ( m_name[ i ] != name[ i ] ) return false;
                if ( name[ i ] == 0 ) return true;
            }
            return true;
        }

        constexpr bool is_executable( )         const noexcept { return ( m_characteristics & section_mem_execute ) != 0; }
        constexpr bool is_readable( )           const noexcept { return ( m_characteristics & section_mem_read ) != 0; }
        constexpr bool is_writable( )           const noexcept { return ( m_characteristics & section_mem_write ) != 0; }
        constexpr bool is_code( )               const noexcept { return ( m_characteristics & section_cnt_code ) != 0; }
        constexpr bool is_initialized_data( )   const noexcept { return ( m_characteristics & section_cnt_initialized_data ) != 0; }
        constexpr bool is_uninitialized_data( ) const noexcept { return ( m_characteristics & section_cnt_uninitialized_data ) != 0; }
        constexpr bool is_discardable( )        const noexcept { return ( m_characteristics & section_mem_discardable ) != 0; }
    };

    struct export_directory_t {
        std::uint32_t m_characteristics;
        std::uint32_t m_time_date_stamp;
        std::uint16_t m_major_version;
        std::uint16_t m_minor_version;
        std::uint32_t m_name;
        std::uint32_t m_base;
        std::uint32_t m_number_of_functions;
        std::uint32_t m_number_of_names;
        std::uint32_t m_address_of_functions;
        std::uint32_t m_address_of_names;
        std::uint32_t m_address_of_names_ordinals;

        constexpr bool is_valid( ) const noexcept {
            return m_address_of_functions != 0
                && m_address_of_names != 0
                && m_address_of_names_ordinals != 0;
        }
    };

    struct import_descriptor_t {
        union {
            std::uint32_t m_characteristics;
            std::uint32_t m_original_first_thunk;
        };
        std::uint32_t m_time_date_stamp;
        std::uint32_t m_forwarder_chain;
        std::uint32_t m_name;
        std::uint32_t m_first_thunk;

        constexpr bool is_terminator( ) const noexcept {
            return m_name == 0 && m_first_thunk == 0;
        }
    };

    struct import_by_name_t {
        std::uint16_t m_hint;
        char          m_name[ 1 ];
    };

    struct thunk_data_64_t {
        union {
            std::uint64_t m_forwarder_string;
            std::uint64_t m_function;
            std::uint64_t m_ordinal;
            std::uint64_t m_address_of_data;
        };

        constexpr bool is_ordinal( ) const noexcept {
            return ( m_ordinal & 0x8000000000000000ull ) != 0;
        }

        constexpr std::uint16_t ordinal( ) const noexcept {
            return static_cast< std::uint16_t >( m_ordinal & 0xFFFF );
        }
    };

    struct thunk_data_32_t {
        union {
            std::uint32_t m_forwarder_string;
            std::uint32_t m_function;
            std::uint32_t m_ordinal;
            std::uint32_t m_address_of_data;
        };

        constexpr bool is_ordinal( ) const noexcept {
            return ( m_ordinal & 0x80000000u ) != 0;
        }

        constexpr std::uint16_t ordinal( ) const noexcept {
            return static_cast< std::uint16_t >( m_ordinal & 0xFFFF );
        }
    };

    struct base_relocation_t {
        std::uint32_t m_virtual_address;
        std::uint32_t m_size_of_block;

        constexpr std::uint32_t entry_count( ) const noexcept {
            return ( m_size_of_block - sizeof( base_relocation_t ) ) / sizeof( std::uint16_t );
        }
    };

    struct base_relocation_entry_t {
        std::uint16_t m_offset : 12;
        std::uint16_t m_type : 4;
    };

    struct debug_directory_t {
        std::uint32_t m_characteristics;
        std::uint32_t m_time_date_stamp;
        std::uint16_t m_major_version;
        std::uint16_t m_minor_version;
        std::uint32_t m_type;
        std::uint32_t m_size_of_data;
        std::uint32_t m_address_of_raw_data;
        std::uint32_t m_pointer_to_raw_data;
    };

    struct codeview_info_pdb70_t {
        std::uint32_t m_signature;
        std::uint8_t  m_guid[ 16 ];
        std::uint32_t m_age;
        char          m_pdb_file_name[ 1 ];
    };

    struct codeview_info_pdb20_t {
        std::uint32_t m_signature;
        std::uint32_t m_offset;
        std::uint32_t m_time_date_stamp;
        std::uint32_t m_age;
        char          m_pdb_file_name[ 1 ];
    };

    struct tls_directory_64_t {
        std::uint64_t m_start_address_of_raw_data;
        std::uint64_t m_end_address_of_raw_data;
        std::uint64_t m_address_of_index;
        std::uint64_t m_address_of_callbacks;
        std::uint32_t m_size_of_zero_fill;
        std::uint32_t m_characteristics;
    };

    struct tls_directory_32_t {
        std::uint32_t m_start_address_of_raw_data;
        std::uint32_t m_end_address_of_raw_data;
        std::uint32_t m_address_of_index;
        std::uint32_t m_address_of_callbacks;
        std::uint32_t m_size_of_zero_fill;
        std::uint32_t m_characteristics;
    };

    struct resource_directory_t {
        std::uint32_t m_characteristics;
        std::uint32_t m_time_date_stamp;
        std::uint16_t m_major_version;
        std::uint16_t m_minor_version;
        std::uint16_t m_number_of_named_entries;
        std::uint16_t m_number_of_id_entries;
    };

    struct resource_directory_entry_t {
        union {
            struct {
                std::uint32_t m_name_offset : 31;
                std::uint32_t m_name_is_string : 1;
            };
            std::uint32_t m_name;
            std::uint16_t m_id;
        };
        union {
            std::uint32_t m_offset_to_data;
            struct {
                std::uint32_t m_offset_to_directory : 31;
                std::uint32_t m_data_is_directory : 1;
            };
        };
    };

    struct resource_data_entry_t {
        std::uint32_t m_offset_to_data;
        std::uint32_t m_size;
        std::uint32_t m_code_page;
        std::uint32_t m_reserved;
    };

    struct runtime_function_t {
        std::uint32_t m_begin_address;
        std::uint32_t m_end_address;
        std::uint32_t m_unwind_info_address;
    };

    struct win_cert_t {
        std::uint32_t m_length;
        std::uint16_t m_revision;
        std::uint16_t m_certificate_type;
        std::uint8_t  m_certificate[ 1 ];
    };

    struct load_config_directory_64_t {
        std::uint32_t m_size;
        std::uint32_t m_time_date_stamp;
        std::uint16_t m_major_version;
        std::uint16_t m_minor_version;
        std::uint32_t m_global_flags_clear;
        std::uint32_t m_global_flags_set;
        std::uint32_t m_critical_section_default_timeout;
        std::uint64_t m_de_commit_free_block_threshold;
        std::uint64_t m_de_commit_total_free_threshold;
        std::uint64_t m_lock_prefix_table;
        std::uint64_t m_maximum_allocation_size;
        std::uint64_t m_virtual_memory_threshold;
        std::uint64_t m_process_affinity_mask;
        std::uint32_t m_process_heap_flags;
        std::uint16_t m_csd_version;
        std::uint16_t m_dependent_load_flags;
        std::uint64_t m_edit_list;
        std::uint64_t m_security_cookie;
        std::uint64_t m_se_handler_table;
        std::uint64_t m_se_handler_count;
        std::uint64_t m_guard_cf_check_function_pointer;
        std::uint64_t m_guard_cf_dispatch_function_pointer;
        std::uint64_t m_guard_cf_function_table;
        std::uint64_t m_guard_cf_function_count;
        std::uint32_t m_guard_flags;
    };

#pragma pack(pop)

    struct pe_image_t {
        std::uint64_t m_base;

        constexpr explicit pe_image_t( std::uint64_t base ) noexcept
            : m_base( base ) {
        }

        dos_header_t* dos_header( ) const noexcept {
            return reinterpret_cast< dos_header_t* >( m_base );
        }

        nt_headers_t* nt_headers( ) const noexcept {
            auto dos = dos_header( );
            if ( !dos || !dos->is_valid( ) ) return nullptr;
            return reinterpret_cast< nt_headers_t* >( m_base + dos->m_lfanew );
        }

        section_header_t* first_section( ) const noexcept {
            auto nt = nt_headers( );
            if ( !nt || !nt->is_valid( ) ) return nullptr;
            return reinterpret_cast< section_header_t* >(
                reinterpret_cast< std::uintptr_t >( nt ) +
                nt->m_size_of_optional_header( ) + 0x18 );
        }

        std::uint16_t section_count( ) const noexcept {
            auto nt = nt_headers( );
            return nt ? nt->m_number_of_sections( ) : 0;
        }

        bool is_valid( ) const noexcept {
            if ( m_base == 0 ) return false;
            auto dos = dos_header( );
            if ( !dos->is_valid( ) ) return false;
            auto nt = nt_headers( );
            return nt && nt->is_valid( );
        }

        template<typename T = void*>
        T rva_to_ptr( std::uint32_t rva ) const noexcept {
            return reinterpret_cast< T >( m_base + rva );
        }

        section_header_t* find_section( const char* name ) const noexcept {
            auto sections = first_section( );
            if ( !sections ) return nullptr;

            std::uint16_t count = section_count( );
            for ( std::uint16_t i = 0; i < count; ++i ) {
                if ( sections[ i ].is_named( name ) )
                    return &sections[ i ];
            }
            return nullptr;
        }

        section_header_t* section_from_rva( std::uint32_t rva ) const noexcept {
            auto sections = first_section( );
            if ( !sections ) return nullptr;

            std::uint16_t count = section_count( );
            for ( std::uint16_t i = 0; i < count; ++i ) {
                std::uint32_t start = sections[ i ].m_virtual_address;
                std::uint32_t end = start + sections[ i ].m_virtual_size;
                if ( rva >= start && rva < end )
                    return &sections[ i ];
            }
            return nullptr;
        }

        export_directory_t* export_directory( ) const noexcept {
            auto nt = nt_headers( );
            if ( !nt ) return nullptr;
            const auto& dir = nt->m_export_table( );
            if ( !dir.is_valid( ) ) return nullptr;
            return dir.as_rva< export_directory_t* >( m_base );
        }

        import_descriptor_t* import_directory( ) const noexcept {
            auto nt = nt_headers( );
            if ( !nt ) return nullptr;
            const auto& dir = nt->m_import_table( );
            if ( !dir.is_valid( ) ) return nullptr;
            return dir.as_rva< import_descriptor_t* >( m_base );
        }

        debug_directory_t* debug_directory( std::uint32_t& out_count ) const noexcept {
            out_count = 0;
            auto nt = nt_headers( );
            if ( !nt ) return nullptr;
            const auto& dir = nt->m_debug_table( );
            if ( !dir.is_valid( ) ) return nullptr;
            out_count = dir.m_size / sizeof( debug_directory_t );
            return dir.as_rva< debug_directory_t* >( m_base );
        }

        std::uint64_t size_of_image( ) const noexcept {
            auto nt = nt_headers( );
            return nt ? nt->m_optional_header.m_size_of_image : 0;
        }

        std::uint64_t entry_point( ) const noexcept {
            auto nt = nt_headers( );
            if ( !nt ) return 0;
            return m_base + nt->m_optional_header.m_address_of_entry_point;
        }

        std::uint64_t find_export( const char* name ) const noexcept {
            auto exp = export_directory( );
            if ( !exp || !exp->is_valid( ) ) return 0;

            auto names = rva_to_ptr< std::uint32_t* >( exp->m_address_of_names );
            auto ordinals = rva_to_ptr< std::uint16_t* >( exp->m_address_of_names_ordinals );
            auto functions = rva_to_ptr< std::uint32_t* >( exp->m_address_of_functions );

            for ( std::uint32_t i = 0; i < exp->m_number_of_names; ++i ) {
                const char* export_name = rva_to_ptr< const char* >( names[ i ] );

                const char* a = name;
                const char* b = export_name;
                while ( *a && *a == *b ) { ++a; ++b; }
                if ( *a == 0 && *b == 0 ) {
                    std::uint16_t ord = ordinals[ i ];
                    return m_base + functions[ ord ];
                }
            }
            return 0;
        }
    };

} // namespace pe