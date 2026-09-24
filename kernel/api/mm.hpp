#pragma once

namespace kernel::api::mm {

    __forceinline void* allocate_independent_pages( std::size_t size ) noexcept {
        using fn_t = void* ( std::size_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_allocate_independent_pages,
            size, static_cast< std::uint32_t >( -1 ) );
    }

    __forceinline void free_independent_pages( void* base, std::size_t size ) noexcept {
        using fn_t = void( void*, std::size_t );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_free_independent_pages, base, size );
    }

    __forceinline bool set_page_protection( std::uint64_t va, std::size_t size,
        std::uint64_t protection ) noexcept {
        using fn_t = bool( std::uint64_t, std::size_t, std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_set_page_protection,
            va, size, protection );
    }

    __forceinline void* copy_memory( void* dst, const void* src, std::size_t n ) noexcept {
        using fn_t = void* ( void*, const void*, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_copy_memory, dst, src, n );
    }

    __forceinline std::int32_t copy_virtual_memory( void* source_process, void* source_address,
        void* target_process, void* target_address, std::size_t buffer_size,
        std::uint8_t previous_mode, std::size_t* return_size ) noexcept {
        using fn_t = std::int32_t( void*, void*, void*, void*, std::size_t, std::uint8_t, std::size_t* );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_copy_virtual_memory,
            source_process, source_address, target_process, target_address,
            buffer_size, previous_mode, return_size );
    }

    __forceinline std::uint64_t get_physical_address( const void* va ) noexcept {
        using fn_t = std::uint64_t( const void* );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_get_physical_address, va );
    }

    __forceinline void* get_virtual_for_physical( std::uint64_t pa ) noexcept {
        using fn_t = void* ( std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_get_virtual_for_physical, pa );
    }

    __forceinline void* map_io_space( std::uint64_t pa, std::size_t size,
        std::uint32_t cache_type ) noexcept {
        using fn_t = void* ( std::uint64_t, std::size_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_map_io_space,
            pa, size, cache_type );
    }

    __forceinline void* map_io_space_ex( std::uint64_t pa, std::size_t size,
        std::uint32_t cache_type, std::uint32_t protection ) noexcept {
        using fn_t = void* ( std::uint64_t, std::size_t, std::uint32_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_map_io_space_ex,
            pa, size, cache_type, protection );
    }

    __forceinline void unmap_io_space( void* base, std::size_t size ) noexcept {
        using fn_t = void( void*, std::size_t );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_unmap_io_space, base, size );
    }

    __forceinline void* allocate_contiguous_memory( std::size_t size,
        std::uint64_t highest_acceptable_address ) noexcept {
        using fn_t = void* ( std::size_t, std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_allocate_contiguous_memory,
            size, highest_acceptable_address );
    }

    __forceinline void* allocate_contiguous_memory_specify_cache( std::size_t size,
        std::uint64_t lowest_acceptable_address, std::uint64_t highest_acceptable_address,
        std::uint64_t boundary_address_multiple, std::uint32_t cache_type ) noexcept {
        using fn_t = void* ( std::size_t, std::uint64_t, std::uint64_t, std::uint64_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_allocate_contiguous_memory_specify_cache,
            size, lowest_acceptable_address, highest_acceptable_address,
            boundary_address_multiple, cache_type );
    }

    __forceinline void free_contiguous_memory( void* base ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_free_contiguous_memory, base );
    }

    __forceinline bool is_address_valid( const void* address ) noexcept {
        using fn_t = bool( const void* );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_is_address_valid, address );
    }

    __forceinline void* get_system_routine_address( nt::unicode_string_t* name ) noexcept {
        using fn_t = void* ( nt::unicode_string_t* );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_get_system_routine_address, name );
    }

    __forceinline void* get_physical_memory_ranges( ) noexcept {
        using fn_t = void* ( void );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_get_physical_memory_ranges );
    }

    __forceinline std::uint64_t user_probe_address( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_user_probe_address;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint64_t* >( addr );
    }

    __forceinline std::uint64_t high_memory( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_high_memory;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint64_t* >( addr );
    }

    __forceinline std::uint64_t system_range_start( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_system_range_start;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint64_t* >( addr );
    }

    __forceinline std::int32_t initialize_process_address_space( void* process,
        void* section, std::uint64_t* directory_table_base, std::uint32_t* audit_name,
        void* file_object ) noexcept {
        using fn_t = std::int32_t( void*, void*, std::uint64_t*, std::uint32_t*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_initialize_process_address_space,
            process, section, directory_table_base, audit_name, file_object );
    }

    __forceinline nt::mmpfn_t* pfn_database( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_pfn_database;
        if ( !addr ) return nullptr;
        return *reinterpret_cast< nt::mmpfn_t** >( addr );
    }

    __forceinline nt::mm_unloaded_driver_t* unloaded_drivers( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_unloaded_drivers;
        if ( !addr ) return nullptr;
        return *reinterpret_cast< nt::mm_unloaded_driver_t** >( addr );
    }

    __forceinline std::uint64_t last_unloaded_driver( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_last_unloaded_driver;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint64_t* >( addr );
    }

    __forceinline std::uint32_t unloaded_driver_count( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_unloaded_driver_count;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint32_t* >( addr );
    }

    __forceinline void* pfn_lock( ) noexcept {
        const auto addr = symbols::get( ).m_mm.m_pfn_lock;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline void* allocate_pages_for_mdl( nt::large_integer_t low_address,
        nt::large_integer_t high_address, nt::large_integer_t skip_bytes,
        std::size_t total_bytes ) noexcept {
        using fn_t = void* ( nt::large_integer_t, nt::large_integer_t, nt::large_integer_t, std::size_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_allocate_pages_for_mdl,
            low_address, high_address, skip_bytes, total_bytes );
    }

    __forceinline void free_pages_from_mdl( void* mdl ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_free_pages_from_mdl, mdl );
    }

    __forceinline void* map_locked_pages_specify_cache( void* mdl,
        std::uint8_t access_mode, std::uint32_t cache_type,
        void* requested_address, std::uint32_t bug_check_on_failure,
        std::uint32_t priority ) noexcept {
        using fn_t = void* ( void*, std::uint8_t, std::uint32_t, void*, std::uint32_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_map_locked_pages_specify_cache,
            mdl, access_mode, cache_type, requested_address, bug_check_on_failure, priority );
    }

    __forceinline void unmap_locked_pages( void* base_address, void* mdl ) noexcept {
        using fn_t = void( void*, void* );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_unmap_locked_pages, base_address, mdl );
    }

    __forceinline void probe_and_lock_pages( void* mdl, std::uint8_t access_mode,
        std::uint32_t operation ) noexcept {
        using fn_t = void( void*, std::uint8_t, std::uint32_t );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_probe_and_lock_pages,
            mdl, access_mode, operation );
    }

    __forceinline void unlock_pages( void* mdl ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_unlock_pages, mdl );
    }

    __forceinline void build_mdl_for_non_paged_pool( void* mdl ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_mm.m_build_mdl_for_non_paged_pool, mdl );
    }

    __forceinline std::int32_t map_view_of_section( void* section, void* process,
        void** base_address, std::uint64_t zero_bits, std::size_t commit_size,
        nt::large_integer_t* section_offset, std::size_t* view_size,
        std::uint32_t inherit_disposition, std::uint32_t allocation_type,
        std::uint32_t protection ) noexcept {
        using fn_t = std::int32_t( void*, void*, void**, std::uint64_t, std::size_t,
            nt::large_integer_t*, std::size_t*, std::uint32_t, std::uint32_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_map_view_of_section,
            section, process, base_address, zero_bits, commit_size, section_offset,
            view_size, inherit_disposition, allocation_type, protection );
    }

    __forceinline std::int32_t unmap_view_of_section( void* process, void* base_address ) noexcept {
        using fn_t = std::int32_t( void*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_mm.m_unmap_view_of_section,
            process, base_address );
    }

} // namespace kernel::api::mm

namespace kernel::api::mi {

    __forceinline bool lock_page_table_page( void* pfn, std::uint32_t flags ) noexcept {
        using fn_t = bool( void*, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_lock_page_table_page,
            pfn, flags );
    }

    __forceinline bool is_page_on_bad_list( void* pfn ) noexcept {
        using fn_t = bool( void* );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_is_page_on_bad_list, pfn );
    }

    __forceinline void make_page_bad( void* pfn ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_mi.m_make_page_bad, pfn );
    }

    __forceinline std::int32_t copy_on_write( void* process, void* pte, void* pfn ) noexcept {
        using fn_t = std::int32_t( void*, void*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_copy_on_write, process, pte, pfn );
    }

    __forceinline void remove_vad( void* vad, void* process ) noexcept {
        using fn_t = void( void*, void* );
        symbols::call< fn_t >( symbols::get( ).m_mi.m_remove_vad, vad, process );
    }

    __forceinline std::int32_t insert_vad( void* vad, void* process ) noexcept {
        using fn_t = std::int32_t( void*, void* );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_insert_vad, vad, process );
    }

    __forceinline nt::mmpfn_t* get_pfn_from_page_table( void* pte ) noexcept {
        using fn_t = nt::mmpfn_t* ( void* );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_get_pfn_from_page_table, pte );
    }

    __forceinline std::int32_t initialize_pfn_for_other_process( std::uint64_t pfn,
        void* pte, std::uint64_t pte_frame, void* process ) noexcept {
        using fn_t = std::int32_t( std::uint64_t, void*, std::uint64_t, void* );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_initialize_pfn_for_other_process,
            pfn, pte, pte_frame, process );
    }

    __forceinline void* allocate_vad( void* process, std::uint64_t start_va,
        std::uint64_t end_va, std::uint32_t protection, std::uint32_t vad_type ) noexcept {
        using fn_t = void* ( void*, std::uint64_t, std::uint64_t, std::uint32_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_allocate_vad,
            process, start_va, end_va, protection, vad_type );
    }

    __forceinline void delete_vad( void* vad ) noexcept {
        using fn_t = void( void* );
        symbols::call< fn_t >( symbols::get( ).m_mi.m_delete_vad, vad );
    }

    __forceinline nt::pte_t* get_pte_address( std::uint64_t va ) noexcept {
        using fn_t = nt::pte_t* ( std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_get_pte_address, va );
    }

    __forceinline nt::pde_t* get_pde_address( std::uint64_t va ) noexcept {
        using fn_t = nt::pde_t* ( std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_get_pde_address, va );
    }

    __forceinline nt::pdpte_t* get_ppe_address( std::uint64_t va ) noexcept {
        using fn_t = nt::pdpte_t* ( std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_get_ppe_address, va );
    }

    __forceinline nt::pml4e_t* get_pxe_address( std::uint64_t va ) noexcept {
        using fn_t = nt::pml4e_t* ( std::uint64_t );
        return symbols::call< fn_t >( symbols::get( ).m_mi.m_get_pxe_address, va );
    }

    __forceinline void flush_tb_all( ) noexcept {
        using fn_t = void( void );
        symbols::call< fn_t >( symbols::get( ).m_mi.m_flush_tb_all );
    }

} // namespace kernel::api::mi