#pragma once

namespace std {

    __forceinline bool is_digit( char c ) noexcept { return c >= '0' && c <= '9'; }
    __forceinline bool is_alpha( char c ) noexcept { return ( c >= 'a' && c <= 'z' ) || ( c >= 'A' && c <= 'Z' ); }
    __forceinline bool is_alnum( char c ) noexcept { return is_digit( c ) || is_alpha( c ); }
    __forceinline bool is_space( char c ) noexcept { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f'; }
    __forceinline bool is_upper( char c ) noexcept { return c >= 'A' && c <= 'Z'; }
    __forceinline bool is_lower( char c ) noexcept { return c >= 'a' && c <= 'z'; }
    __forceinline bool is_hex( char c )   noexcept { return is_digit( c ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' ); }
    __forceinline bool is_print( char c ) noexcept { return c >= 0x20 && c < 0x7F; }

    __forceinline char to_lower( char c ) noexcept { return ( c >= 'A' && c <= 'Z' ) ? static_cast< char >( c + 32 ) : c; }
    __forceinline char to_upper( char c ) noexcept { return ( c >= 'a' && c <= 'z' ) ? static_cast< char >( c - 32 ) : c; }

    __forceinline wchar_alias to_lower( wchar_alias c ) noexcept { return ( c >= L'A' && c <= L'Z' ) ? static_cast< wchar_alias >( c + 32 ) : c; }
    __forceinline wchar_alias to_upper( wchar_alias c ) noexcept { return ( c >= L'a' && c <= L'z' ) ? static_cast< wchar_alias >( c - 32 ) : c; }

    __forceinline size_t str_length( const char* s ) noexcept {
        const char* p = s;
        while ( *p ) ++p;
        return static_cast< size_t >( p - s );
    }

    __forceinline size_t str_length_n( const char* s, size_t max ) noexcept {
        size_t n = 0;
        while ( n < max && s[ n ] ) ++n;
        return n;
    }

    __forceinline size_t wstr_length( const wchar_alias* s ) noexcept {
        const wchar_alias* p = s;
        while ( *p ) ++p;
        return static_cast< size_t >( p - s );
    }

    __forceinline size_t wstr_length_n( const wchar_alias* s, size_t max ) noexcept {
        size_t n = 0;
        while ( n < max && s[ n ] ) ++n;
        return n;
    }

    __forceinline char* str_copy( char* dst, const char* src ) noexcept {
        char* r = dst;
        while ( ( *dst++ = *src++ ) != 0 ) { }
        return r;
    }

    __forceinline char* str_copy_n( char* dst, const char* src, size_t n ) noexcept {
        char* r = dst;
        while ( n && ( *dst++ = *src++ ) != 0 ) --n;
        while ( n-- ) *dst++ = 0;
        return r;
    }

    __forceinline wchar_alias* wstr_copy( wchar_alias* dst, const wchar_alias* src ) noexcept {
        wchar_alias* r = dst;
        while ( ( *dst++ = *src++ ) != 0 ) { }
        return r;
    }

    __forceinline wchar_alias* wstr_copy_n( wchar_alias* dst, const wchar_alias* src, size_t n ) noexcept {
        wchar_alias* r = dst;
        while ( n && ( *dst++ = *src++ ) != 0 ) --n;
        while ( n-- ) *dst++ = 0;
        return r;
    }

    __forceinline int str_compare( const char* a, const char* b ) noexcept {
        while ( *a && ( *a == *b ) ) { ++a; ++b; }
        return static_cast< int >( static_cast< uint8_t >( *a ) ) -
            static_cast< int >( static_cast< uint8_t >( *b ) );
    }

    __forceinline int str_compare_n( const char* a, const char* b, size_t n ) noexcept {
        while ( n && *a && ( *a == *b ) ) { ++a; ++b; --n; }
        if ( n == 0 ) return 0;
        return static_cast< int >( static_cast< uint8_t >( *a ) ) -
            static_cast< int >( static_cast< uint8_t >( *b ) );
    }

    __forceinline int wstr_compare( const wchar_alias* a, const wchar_alias* b ) noexcept {
        while ( *a && ( *a == *b ) ) { ++a; ++b; }
        return static_cast< int >( *a ) - static_cast< int >( *b );
    }

    __forceinline int wstr_compare_n( const wchar_alias* a, const wchar_alias* b, size_t n ) noexcept {
        while ( n && *a && ( *a == *b ) ) { ++a; ++b; --n; }
        if ( n == 0 ) return 0;
        return static_cast< int >( *a ) - static_cast< int >( *b );
    }

    __forceinline int str_compare_i( const char* a, const char* b ) noexcept {
        while ( *a && *b ) {
            char ca = to_lower( *a );
            char cb = to_lower( *b );
            if ( ca != cb ) return static_cast< int >( ca ) - static_cast< int >( cb );
            ++a; ++b;
        }
        return static_cast< int >( *a ) - static_cast< int >( *b );
    }

    __forceinline int wstr_compare_i( const wchar_alias* a, const wchar_alias* b ) noexcept {
        while ( *a && *b ) {
            wchar_alias ca = to_lower( *a );
            wchar_alias cb = to_lower( *b );
            if ( ca != cb ) return static_cast< int >( ca ) - static_cast< int >( cb );
            ++a; ++b;
        }
        return static_cast< int >( *a ) - static_cast< int >( *b );
    }

    __forceinline bool str_equal( const char* a, const char* b )                noexcept { return str_compare( a, b ) == 0; }
    __forceinline bool wstr_equal( const wchar_alias* a, const wchar_alias* b ) noexcept { return wstr_compare( a, b ) == 0; }
    __forceinline bool str_equal_i( const char* a, const char* b )              noexcept { return str_compare_i( a, b ) == 0; }
    __forceinline bool wstr_equal_i( const wchar_alias* a, const wchar_alias* b ) noexcept { return wstr_compare_i( a, b ) == 0; }

    __forceinline const char* str_find_char( const char* s, char c ) noexcept {
        while ( *s ) {
            if ( *s == c ) return s;
            ++s;
        }
        return c == 0 ? s : nullptr;
    }

    __forceinline const char* str_find_char_last( const char* s, char c ) noexcept {
        const char* last = nullptr;
        while ( *s ) {
            if ( *s == c ) last = s;
            ++s;
        }
        return last;
    }

    __forceinline const char* str_find( const char* haystack, const char* needle ) noexcept {
        if ( !*needle ) return haystack;
        for ( ; *haystack; ++haystack ) {
            const char* h = haystack;
            const char* n = needle;
            while ( *h && *n && *h == *n ) { ++h; ++n; }
            if ( !*n ) return haystack;
        }
        return nullptr;
    }

    __forceinline const wchar_alias* wstr_find_char( const wchar_alias* s, wchar_alias c ) noexcept {
        while ( *s ) {
            if ( *s == c ) return s;
            ++s;
        }
        return c == 0 ? s : nullptr;
    }

    __forceinline const wchar_alias* wstr_find_char_last( const wchar_alias* s, wchar_alias c ) noexcept {
        const wchar_alias* last = nullptr;
        while ( *s ) {
            if ( *s == c ) last = s;
            ++s;
        }
        return last;
    }

    __forceinline const wchar_alias* wstr_find( const wchar_alias* haystack, const wchar_alias* needle ) noexcept {
        if ( !*needle ) return haystack;
        for ( ; *haystack; ++haystack ) {
            const wchar_alias* h = haystack;
            const wchar_alias* n = needle;
            while ( *h && *n && *h == *n ) { ++h; ++n; }
            if ( !*n ) return haystack;
        }
        return nullptr;
    }

    __forceinline bool str_starts_with( const char* s, const char* prefix ) noexcept {
        while ( *prefix ) {
            if ( *s != *prefix ) return false;
            ++s; ++prefix;
        }
        return true;
    }

    __forceinline bool str_ends_with( const char* s, const char* suffix ) noexcept {
        size_t sl = str_length( s );
        size_t xl = str_length( suffix );
        if ( xl > sl ) return false;
        return str_compare( s + sl - xl, suffix ) == 0;
    }

    __forceinline bool wstr_starts_with( const wchar_alias* s, const wchar_alias* prefix ) noexcept {
        while ( *prefix ) {
            if ( *s != *prefix ) return false;
            ++s; ++prefix;
        }
        return true;
    }

    __forceinline bool wstr_ends_with( const wchar_alias* s, const wchar_alias* suffix ) noexcept {
        size_t sl = wstr_length( s );
        size_t xl = wstr_length( suffix );
        if ( xl > sl ) return false;
        return wstr_compare( s + sl - xl, suffix ) == 0;
    }

    __forceinline char* str_concat( char* dst, const char* src ) noexcept {
        char* r = dst;
        while ( *dst ) ++dst;
        while ( ( *dst++ = *src++ ) != 0 ) { }
        return r;
    }

    __forceinline wchar_alias* wstr_concat( wchar_alias* dst, const wchar_alias* src ) noexcept {
        wchar_alias* r = dst;
        while ( *dst ) ++dst;
        while ( ( *dst++ = *src++ ) != 0 ) { }
        return r;
    }

    __forceinline void str_to_lower( char* s )         noexcept { while ( *s ) { *s = to_lower( *s ); ++s; } }
    __forceinline void str_to_upper( char* s )         noexcept { while ( *s ) { *s = to_upper( *s ); ++s; } }
    __forceinline void wstr_to_lower( wchar_alias* s ) noexcept { while ( *s ) { *s = to_lower( *s ); ++s; } }
    __forceinline void wstr_to_upper( wchar_alias* s ) noexcept { while ( *s ) { *s = to_upper( *s ); ++s; } }

    __forceinline void str_reverse( char* s ) noexcept {
        size_t n = str_length( s );
        if ( n < 2 ) return;
        size_t i = 0, j = n - 1;
        while ( i < j ) {
            char t = s[ i ];
            s[ i ] = s[ j ];
            s[ j ] = t;
            ++i; --j;
        }
    }

    __forceinline uint64_t str_hash( const char* s ) noexcept {
        uint64_t h = 0xCBF29CE484222325ull;
        while ( *s ) {
            h ^= static_cast< uint8_t >( *s++ );
            h *= 0x100000001B3ull;
        }
        return h;
    }

    __forceinline uint64_t wstr_hash( const wchar_alias* s ) noexcept {
        uint64_t h = 0xCBF29CE484222325ull;
        while ( *s ) {
            uint16_t c = *s++;
            h ^= static_cast< uint8_t >( c & 0xFF );        h *= 0x100000001B3ull;
            h ^= static_cast< uint8_t >( ( c >> 8 ) & 0xFF ); h *= 0x100000001B3ull;
        }
        return h;
    }

    __forceinline uint64_t str_hash_i( const char* s ) noexcept {
        uint64_t h = 0xCBF29CE484222325ull;
        while ( *s ) {
            uint8_t c = static_cast< uint8_t >( to_lower( *s++ ) );
            h ^= c;
            h *= 0x100000001B3ull;
        }
        return h;
    }

    __forceinline uint64_t wstr_hash_i( const wchar_alias* s ) noexcept {
        uint64_t h = 0xCBF29CE484222325ull;
        while ( *s ) {
            uint16_t c = to_lower( *s++ );
            h ^= static_cast< uint8_t >( c & 0xFF );        h *= 0x100000001B3ull;
            h ^= static_cast< uint8_t >( ( c >> 8 ) & 0xFF ); h *= 0x100000001B3ull;
        }
        return h;
    }

    __forceinline int64_t str_to_int( const char* s, int base = 10 ) noexcept {
        while ( is_space( *s ) ) ++s;

        bool negative = false;
        if ( *s == '-' ) { negative = true; ++s; }
        else if ( *s == '+' ) { ++s; }

        if ( base == 16 && s[ 0 ] == '0' && ( s[ 1 ] == 'x' || s[ 1 ] == 'X' ) )
            s += 2;

        int64_t result = 0;
        while ( *s ) {
            int digit = -1;
            if ( is_digit( *s ) )              digit = *s - '0';
            else if ( *s >= 'a' && *s <= 'z' ) digit = *s - 'a' + 10;
            else if ( *s >= 'A' && *s <= 'Z' ) digit = *s - 'A' + 10;

            if ( digit < 0 || digit >= base ) break;
            result = result * base + digit;
            ++s;
        }
        return negative ? -result : result;
    }

    __forceinline uint64_t str_to_uint( const char* s, int base = 10 ) noexcept {
        while ( is_space( *s ) ) ++s;
        if ( *s == '+' ) ++s;

        if ( base == 16 && s[ 0 ] == '0' && ( s[ 1 ] == 'x' || s[ 1 ] == 'X' ) )
            s += 2;

        uint64_t result = 0;
        while ( *s ) {
            int digit = -1;
            if ( is_digit( *s ) )              digit = *s - '0';
            else if ( *s >= 'a' && *s <= 'z' ) digit = *s - 'a' + 10;
            else if ( *s >= 'A' && *s <= 'Z' ) digit = *s - 'A' + 10;

            if ( digit < 0 || digit >= base ) break;
            result = result * base + digit;
            ++s;
        }
        return result;
    }

    __forceinline size_t int_to_str( int64_t value, char* buf, int base = 10 ) noexcept {
        char   tmp[ 32 ];
        size_t n = 0;
        bool   negative = false;

        if ( value < 0 && base == 10 ) {
            negative = true;
            value = -value;
        }

        uint64_t u = static_cast< uint64_t >( value );

        if ( u == 0 ) tmp[ n++ ] = '0';
        while ( u > 0 ) {
            int digit = static_cast< int >( u % base );
            tmp[ n++ ] = static_cast< char >( digit < 10 ? '0' + digit : 'a' + digit - 10 );
            u /= base;
        }

        size_t out = 0;
        if ( negative ) buf[ out++ ] = '-';
        while ( n > 0 ) buf[ out++ ] = tmp[ --n ];
        buf[ out ] = 0;
        return out;
    }

    __forceinline size_t uint_to_str( uint64_t value, char* buf, int base = 10 ) noexcept {
        char   tmp[ 32 ];
        size_t n = 0;

        if ( value == 0 ) tmp[ n++ ] = '0';
        while ( value > 0 ) {
            int digit = static_cast< int >( value % base );
            tmp[ n++ ] = static_cast< char >( digit < 10 ? '0' + digit : 'a' + digit - 10 );
            value /= base;
        }

        size_t out = 0;
        while ( n > 0 ) buf[ out++ ] = tmp[ --n ];
        buf[ out ] = 0;
        return out;
    }

    __forceinline size_t uint_to_hex( uint64_t value, char* buf, bool upper = false ) noexcept {
        char   tmp[ 32 ];
        size_t n = 0;
        char   base = upper ? 'A' : 'a';

        if ( value == 0 ) tmp[ n++ ] = '0';
        while ( value > 0 ) {
            int digit = static_cast< int >( value & 0xF );
            tmp[ n++ ] = static_cast< char >( digit < 10 ? '0' + digit : base + digit - 10 );
            value >>= 4;
        }

        size_t out = 0;
        while ( n > 0 ) buf[ out++ ] = tmp[ --n ];
        buf[ out ] = 0;
        return out;
    }

    __forceinline size_t wstr_to_str( char* dst, const wchar_alias* src, size_t max ) noexcept {
        size_t n = 0;
        while ( *src && n + 1 < max ) {
            dst[ n++ ] = static_cast< char >( *src & 0xFF );
            ++src;
        }
        dst[ n ] = 0;
        return n;
    }

    __forceinline size_t str_to_wstr( wchar_alias* dst, const char* src, size_t max ) noexcept {
        size_t n = 0;
        while ( *src && n + 1 < max ) {
            dst[ n++ ] = static_cast< wchar_alias >( static_cast< uint8_t >( *src ) );
            ++src;
        }
        dst[ n ] = 0;
        return n;
    }

} // namespace std