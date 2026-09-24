#pragma once

namespace core::log {

    enum class level : std::uint32_t {
        trace = 0,
        info = 1,
        warn = 2,
        error = 3,
        fatal = 4
    };

#ifdef DEBUG_LOG
    constexpr level min_level = level::trace;
    constexpr bool  enabled = true;
#else
    constexpr level min_level = level::error;
    constexpr bool  enabled = false;
#endif

    constexpr std::uint32_t component_id = 77;
    constexpr std::uint32_t dbg_level = 0;

    namespace detail {

        __forceinline const char* level_tag( level lv ) noexcept {
            switch ( lv ) {
            case level::trace: return "trace";
            case level::info:  return "info";
            case level::warn:  return "warn";
            case level::error: return "error";
            case level::fatal: return "fatal";
            }
            return "?????";
        }

        __forceinline void append( char* dst, std::size_t& pos, std::size_t cap,
            const char* src ) noexcept {
            if ( !src || pos + 1 >= cap ) return;
            const std::size_t len = std::str_length( src );
            const std::size_t space = cap - pos - 1;
            const std::size_t n = len < space ? len : space;
            for ( std::size_t i = 0; i < n; ++i )
                dst[ pos + i ] = src[ i ];
            pos += n;
        }

        template<std::size_t n>
        __forceinline void append_lit( char* dst, std::size_t& pos, std::size_t cap,
            const char( &src )[ n ] ) noexcept {
            constexpr std::size_t len = n - 1;
            if ( pos + 1 >= cap ) return;
            const std::size_t space = cap - pos - 1;
            const std::size_t take = len < space ? len : space;
            for ( std::size_t i = 0; i < take; ++i )
                dst[ pos + i ] = src[ i ];
            pos += take;
        }

        template<class... args_t>
        __forceinline void emit( level lv, const char* component,
            const char* fmt, args_t... args ) noexcept {
            if constexpr ( !enabled ) {
                ( void )lv; ( void )component; ( void )fmt;
                return;
            }
            else {
                if ( static_cast< std::uint32_t >( lv ) <
                    static_cast< std::uint32_t >( min_level ) )
                    return;

                char        buffer[ 512 ];
                std::size_t pos = 0;

                append_lit( buffer, pos, sizeof( buffer ), "[rockstar][" );
                append( buffer, pos, sizeof( buffer ), level_tag( lv ) );
                append_lit( buffer, pos, sizeof( buffer ), "][" );
                append( buffer, pos, sizeof( buffer ), component );
                append_lit( buffer, pos, sizeof( buffer ), "] " );
                append( buffer, pos, sizeof( buffer ), fmt );
                buffer[ pos ] = '\0';

                kernel::api::dbg::print_ex( component_id, dbg_level, buffer, args... );
            }
        }

    } // namespace detail

    template<class... args_t>
    __forceinline void trace( const char* component, const char* fmt, args_t... args ) noexcept {
        detail::emit( level::trace, component, fmt, args... );
    }

    template<class... args_t>
    __forceinline void info( const char* component, const char* fmt, args_t... args ) noexcept {
        detail::emit( level::info, component, fmt, args... );
    }

    template<class... args_t>
    __forceinline void warn( const char* component, const char* fmt, args_t... args ) noexcept {
        detail::emit( level::warn, component, fmt, args... );
    }

    template<class... args_t>
    __forceinline void error( const char* component, const char* fmt, args_t... args ) noexcept {
        detail::emit( level::error, component, fmt, args... );
    }

    template<class... args_t>
    __forceinline void fatal( const char* component, const char* fmt, args_t... args ) noexcept {
        detail::emit( level::fatal, component, fmt, args... );
    }

    __forceinline void hex_dump( const char* component, const void* data,
        std::size_t size, std::size_t bytes_per_line = 16 ) noexcept {
        if constexpr ( !enabled ) {
            ( void )component; ( void )data; ( void )size; ( void )bytes_per_line;
            return;
        }
        else {
            if ( !data || !size ) return;

            const auto bytes = static_cast< const std::uint8_t* >( data );
            char        line[ 256 ];
            std::size_t pos = 0;

            for ( std::size_t i = 0; i < size; ++i ) {
                if ( i % bytes_per_line == 0 ) {
                    if ( i > 0 ) {
                        line[ pos ] = '\0';
                        info( component, "%s\n", line );
                        pos = 0;
                    }

                    char offset_buf[ 16 ];
                    std::size_t olen = std::uint_to_hex(
                        static_cast< std::uint64_t >( i ), offset_buf );

                    for ( std::size_t j = olen; j < 8; ++j )
                        line[ pos++ ] = '0';
                    for ( std::size_t j = 0; j < olen; ++j )
                        line[ pos++ ] = offset_buf[ j ];

                    line[ pos++ ] = ':';
                    line[ pos++ ] = ' ';
                }

                char hex_buf[ 4 ];
                std::size_t hlen = std::uint_to_hex(
                    static_cast< std::uint64_t >( bytes[ i ] ), hex_buf );

                if ( hlen == 1 ) line[ pos++ ] = '0';
                for ( std::size_t j = 0; j < hlen; ++j )
                    line[ pos++ ] = hex_buf[ j ];
                line[ pos++ ] = ' ';
            }

            if ( pos > 0 ) {
                line[ pos ] = '\0';
                info( component, "%s\n", line );
            }
        }
    }

} // namespace core::log