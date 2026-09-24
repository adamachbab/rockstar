#pragma once

namespace std {

    __forceinline void* mem_copy( void* dst, const void* src, size_t n ) noexcept {
        uint8_t* d = static_cast< uint8_t* >( dst );
        const uint8_t* s = static_cast< const uint8_t* >( src );

        while ( n >= 8 ) {
            *reinterpret_cast< uint64_t* >( d ) = *reinterpret_cast< const uint64_t* >( s );
            d += 8; s += 8; n -= 8;
        }
        while ( n >= 4 ) {
            *reinterpret_cast< uint32_t* >( d ) = *reinterpret_cast< const uint32_t* >( s );
            d += 4; s += 4; n -= 4;
        }
        while ( n-- ) *d++ = *s++;
        return dst;
    }

    __forceinline void* mem_move( void* dst, const void* src, size_t n ) noexcept {
        uint8_t* d = static_cast< uint8_t* >( dst );
        const uint8_t* s = static_cast< const uint8_t* >( src );

        if ( d == s || n == 0 ) return dst;

        const uintptr_t pd = reinterpret_cast< uintptr_t >( d );
        const uintptr_t ps = reinterpret_cast< uintptr_t >( s );

        if ( pd < ps || pd >= ps + n )
            return mem_copy( dst, src, n );

        d += n; s += n;
        while ( n-- ) *--d = *--s;
        return dst;
    }

    __forceinline void* mem_set( void* dst, int value, size_t n ) noexcept {
        uint8_t* d = static_cast< uint8_t* >( dst );
        uint8_t  v = static_cast< uint8_t >( value );

        uint64_t v64 = v;
        v64 |= v64 << 8;
        v64 |= v64 << 16;
        v64 |= v64 << 32;

        while ( n >= 8 ) {
            *reinterpret_cast< uint64_t* >( d ) = v64;
            d += 8; n -= 8;
        }
        while ( n-- ) *d++ = v;
        return dst;
    }

    __forceinline void* mem_zero( void* dst, size_t n ) noexcept {
        return mem_set( dst, 0, n );
    }

    __forceinline void mem_zero_secure( void* dst, size_t n ) noexcept {
        volatile uint8_t* d = static_cast< volatile uint8_t* >( dst );
        while ( n-- ) *d++ = 0;
    }

    __forceinline int mem_compare( const void* a, const void* b, size_t n ) noexcept {
        const uint8_t* p1 = static_cast< const uint8_t* >( a );
        const uint8_t* p2 = static_cast< const uint8_t* >( b );

        while ( n >= 8 ) {
            uint64_t v1 = *reinterpret_cast< const uint64_t* >( p1 );
            uint64_t v2 = *reinterpret_cast< const uint64_t* >( p2 );
            if ( v1 != v2 ) break;
            p1 += 8; p2 += 8; n -= 8;
        }
        while ( n-- ) {
            if ( *p1 != *p2 ) return static_cast< int >( *p1 ) - static_cast< int >( *p2 );
            ++p1; ++p2;
        }
        return 0;
    }

    __forceinline bool mem_equal( const void* a, const void* b, size_t n ) noexcept {
        return mem_compare( a, b, n ) == 0;
    }

    __forceinline bool mem_equal_secure( const void* a, const void* b, size_t n ) noexcept {
        const volatile uint8_t* p1 = static_cast< const volatile uint8_t* >( a );
        const volatile uint8_t* p2 = static_cast< const volatile uint8_t* >( b );
        uint8_t diff = 0;
        while ( n-- ) diff |= ( *p1++ ^ *p2++ );
        return diff == 0;
    }

    __forceinline const void* mem_find( const void* haystack, size_t hay_size,
        const void* needle, size_t needle_size ) noexcept {
        if ( needle_size == 0 || hay_size < needle_size ) return nullptr;

        const uint8_t* h = static_cast< const uint8_t* >( haystack );
        const uint8_t* n = static_cast< const uint8_t* >( needle );
        const uint8_t  first = n[ 0 ];
        size_t         limit = hay_size - needle_size;

        for ( size_t i = 0; i <= limit; ++i ) {
            if ( h[ i ] == first && mem_equal( h + i, n, needle_size ) )
                return h + i;
        }
        return nullptr;
    }

    __forceinline const void* mem_find_byte( const void* buf, int value, size_t n ) noexcept {
        const uint8_t* p = static_cast< const uint8_t* >( buf );
        uint8_t        v = static_cast< uint8_t >( value );
        while ( n-- ) {
            if ( *p == v ) return p;
            ++p;
        }
        return nullptr;
    }

    __forceinline void mem_swap( void* a, void* b, size_t n ) noexcept {
        uint8_t* p1 = static_cast< uint8_t* >( a );
        uint8_t* p2 = static_cast< uint8_t* >( b );

        while ( n >= 8 ) {
            uint64_t tmp = *reinterpret_cast< uint64_t* >( p1 );
            *reinterpret_cast< uint64_t* >( p1 ) = *reinterpret_cast< uint64_t* >( p2 );
            *reinterpret_cast< uint64_t* >( p2 ) = tmp;
            p1 += 8; p2 += 8; n -= 8;
        }
        while ( n-- ) {
            uint8_t tmp = *p1;
            *p1++ = *p2;
            *p2++ = tmp;
        }
    }

    __forceinline void mem_reverse( void* buf, size_t n ) noexcept {
        if ( n < 2 ) return;
        uint8_t* p = static_cast< uint8_t* >( buf );
        size_t i = 0, j = n - 1;
        while ( i < j ) {
            uint8_t tmp = p[ i ];
            p[ i ] = p[ j ];
            p[ j ] = tmp;
            ++i; --j;
        }
    }

    __forceinline void mem_xor( void* dst, const void* src, size_t n ) noexcept {
        uint8_t* d = static_cast< uint8_t* >( dst );
        const uint8_t* s = static_cast< const uint8_t* >( src );

        while ( n >= 8 ) {
            *reinterpret_cast< uint64_t* >( d ) ^= *reinterpret_cast< const uint64_t* >( s );
            d += 8; s += 8; n -= 8;
        }
        while ( n-- ) *d++ ^= *s++;
    }

    __forceinline void mem_xor_key( void* dst, const void* key, size_t n, size_t key_size ) noexcept {
        uint8_t* d = static_cast< uint8_t* >( dst );
        const uint8_t* k = static_cast< const uint8_t* >( key );
        for ( size_t i = 0; i < n; ++i )
            d[ i ] ^= k[ i % key_size ];
    }

    __forceinline uint64_t mem_hash_fnv1a( const void* data, size_t n ) noexcept {
        const uint8_t* p = static_cast< const uint8_t* >( data );
        uint64_t       h = 0xCBF29CE484222325ull;
        while ( n-- ) {
            h ^= *p++;
            h *= 0x100000001B3ull;
        }
        return h;
    }

    __forceinline uint32_t mem_hash_fnv1a_32( const void* data, size_t n ) noexcept {
        const uint8_t* p = static_cast< const uint8_t* >( data );
        uint32_t       h = 0x811C9DC5u;
        while ( n-- ) {
            h ^= *p++;
            h *= 0x01000193u;
        }
        return h;
    }

    __forceinline bool is_aligned( const void* ptr, size_t alignment ) noexcept {
        return ( reinterpret_cast< uintptr_t >( ptr ) & ( alignment - 1 ) ) == 0;
    }

    __forceinline void* align_ptr_up( void* ptr, size_t alignment ) noexcept {
        uintptr_t p = reinterpret_cast< uintptr_t >( ptr );
        return reinterpret_cast< void* >( ( p + alignment - 1 ) & ~( alignment - 1 ) );
    }

    __forceinline void* align_ptr_down( void* ptr, size_t alignment ) noexcept {
        uintptr_t p = reinterpret_cast< uintptr_t >( ptr );
        return reinterpret_cast< void* >( p & ~( alignment - 1 ) );
    }

    __forceinline size_t align_size_up( size_t n, size_t alignment ) noexcept {
        return ( n + alignment - 1 ) & ~( alignment - 1 );
    }

    __forceinline size_t align_size_down( size_t n, size_t alignment ) noexcept {
        return n & ~( alignment - 1 );
    }

    template<typename T>
    __forceinline T read_unaligned( const void* ptr ) noexcept {
        T value;
        mem_copy( &value, ptr, sizeof( T ) );
        return value;
    }

    template<typename T>
    __forceinline void write_unaligned( void* ptr, const T& value ) noexcept {
        mem_copy( ptr, &value, sizeof( T ) );
    }

    __forceinline uint16_t byte_swap_16( uint16_t v ) noexcept {
        return static_cast< uint16_t >( ( v << 8 ) | ( v >> 8 ) );
    }

    __forceinline uint32_t byte_swap_32( uint32_t v ) noexcept {
        return ( v << 24 ) |
            ( ( v << 8 ) & 0x00FF0000u ) |
            ( ( v >> 8 ) & 0x0000FF00u ) |
            ( v >> 24 );
    }

    __forceinline uint64_t byte_swap_64( uint64_t v ) noexcept {
        return ( v << 56 ) |
            ( ( v << 40 ) & 0x00FF000000000000ull ) |
            ( ( v << 24 ) & 0x0000FF0000000000ull ) |
            ( ( v << 8 ) & 0x000000FF00000000ull ) |
            ( ( v >> 8 ) & 0x00000000FF000000ull ) |
            ( ( v >> 24 ) & 0x0000000000FF0000ull ) |
            ( ( v >> 40 ) & 0x000000000000FF00ull ) |
            ( v >> 56 );
    }

    __forceinline uint32_t rotate_left_32( uint32_t v, uint32_t n )  noexcept { return ( v << ( n & 31 ) ) | ( v >> ( ( 32 - n ) & 31 ) ); }
    __forceinline uint32_t rotate_right_32( uint32_t v, uint32_t n ) noexcept { return ( v >> ( n & 31 ) ) | ( v << ( ( 32 - n ) & 31 ) ); }
    __forceinline uint64_t rotate_left_64( uint64_t v, uint32_t n )  noexcept { return ( v << ( n & 63 ) ) | ( v >> ( ( 64 - n ) & 63 ) ); }
    __forceinline uint64_t rotate_right_64( uint64_t v, uint32_t n ) noexcept { return ( v >> ( n & 63 ) ) | ( v << ( ( 64 - n ) & 63 ) ); }

    __forceinline uint32_t count_leading_zeros_32( uint32_t v ) noexcept {
        if ( v == 0 ) return 32;
        uint32_t n = 0;
        if ( ( v & 0xFFFF0000u ) == 0 ) { n += 16; v <<= 16; }
        if ( ( v & 0xFF000000u ) == 0 ) { n += 8;  v <<= 8; }
        if ( ( v & 0xF0000000u ) == 0 ) { n += 4;  v <<= 4; }
        if ( ( v & 0xC0000000u ) == 0 ) { n += 2;  v <<= 2; }
        if ( ( v & 0x80000000u ) == 0 ) { n += 1; }
        return n;
    }

    __forceinline uint32_t count_trailing_zeros_32( uint32_t v ) noexcept {
        if ( v == 0 ) return 32;
        uint32_t n = 0;
        if ( ( v & 0x0000FFFFu ) == 0 ) { n += 16; v >>= 16; }
        if ( ( v & 0x000000FFu ) == 0 ) { n += 8;  v >>= 8; }
        if ( ( v & 0x0000000Fu ) == 0 ) { n += 4;  v >>= 4; }
        if ( ( v & 0x00000003u ) == 0 ) { n += 2;  v >>= 2; }
        if ( ( v & 0x00000001u ) == 0 ) { n += 1; }
        return n;
    }

    __forceinline uint32_t popcount_32( uint32_t v ) noexcept {
        v = v - ( ( v >> 1 ) & 0x55555555u );
        v = ( v & 0x33333333u ) + ( ( v >> 2 ) & 0x33333333u );
        v = ( v + ( v >> 4 ) ) & 0x0F0F0F0Fu;
        return ( v * 0x01010101u ) >> 24;
    }

    __forceinline uint32_t popcount_64( uint64_t v ) noexcept {
        v = v - ( ( v >> 1 ) & 0x5555555555555555ull );
        v = ( v & 0x3333333333333333ull ) + ( ( v >> 2 ) & 0x3333333333333333ull );
        v = ( v + ( v >> 4 ) ) & 0x0F0F0F0F0F0F0F0Full;
        return static_cast< uint32_t >( ( v * 0x0101010101010101ull ) >> 56 );
    }

} // namespace std