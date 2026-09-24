#pragma once

namespace kernel::api::dbg {

    template<class... args_t>
    __forceinline std::int32_t print( const char* format, args_t... va_args ) noexcept {
        const auto addr = symbols::get( ).m_dbg.m_print;
        if ( !addr ) return 0;
        using fn_t = std::int32_t( * )( const char*, ... );
        return reinterpret_cast< fn_t >( addr )( format, va_args... );
    }

    template<class... args_t>
    __forceinline std::int32_t print_ex( std::uint32_t component_id,
        std::uint32_t level, const char* format, args_t... va_args ) noexcept {
        const auto addr = symbols::get( ).m_dbg.m_print_ex;
        if ( !addr ) return 0;
        using fn_t = std::int32_t( * )( std::uint32_t, std::uint32_t, const char*, ... );
        return reinterpret_cast< fn_t >( addr )( component_id, level, format, va_args... );
    }

    __forceinline std::uint32_t nt_global_flag( ) noexcept {
        const auto addr = symbols::get( ).m_dbg.m_nt_global_flag;
        if ( !addr ) return 0;
        return *reinterpret_cast< std::uint32_t* >( addr );
    }

    __forceinline void break_point( ) noexcept {
        using fn_t = void( void );
        symbols::call< fn_t >( symbols::get( ).m_dbg.m_break_point );
    }

    __forceinline std::uint32_t query_filter_state( std::uint32_t component_id,
        std::uint32_t level ) noexcept {
        using fn_t = std::uint32_t( std::uint32_t, std::uint32_t );
        return symbols::call< fn_t >( symbols::get( ).m_dbg.m_query_debug_filter_state,
            component_id, level );
    }

    __forceinline std::int32_t set_filter_state( std::uint32_t component_id,
        std::uint32_t level, std::uint8_t state ) noexcept {
        using fn_t = std::int32_t( std::uint32_t, std::uint32_t, std::uint8_t );
        return symbols::call< fn_t >( symbols::get( ).m_dbg.m_set_debug_filter_state,
            component_id, level, state );
    }

} // namespace kernel::api::dbg