#pragma once

namespace std {

    template<typename T>
    __forceinline const T& min_of( const T& a, const T& b ) noexcept { return ( b < a ) ? b : a; }

    template<typename T>
    __forceinline const T& max_of( const T& a, const T& b ) noexcept { return ( a < b ) ? b : a; }

    template<typename T, typename U>
    __forceinline auto min_of( T a, U b ) noexcept -> decltype( a < b ? a : b ) { return a < b ? a : b; }

    template<typename T, typename U>
    __forceinline auto max_of( T a, U b ) noexcept -> decltype( a < b ? b : a ) { return a < b ? b : a; }

    template<typename T>
    __forceinline const T& clamp( const T& v, const T& lo, const T& hi ) noexcept {
        return v < lo ? lo : ( hi < v ? hi : v );
    }

    template<typename T>
    __forceinline T abs_of( T v ) noexcept { return v < 0 ? -v : v; }

    template<typename T>
    __forceinline void swap( T& a, T& b ) noexcept {
        T t = a; a = b; b = t;
    }

    template<typename T>
    __forceinline void swap_array( T* a, T* b, size_t n ) noexcept {
        for ( size_t i = 0; i < n; ++i ) swap( a[ i ], b[ i ] );
    }

    template<typename T>
    __forceinline T* find( T* first, T* last, const T& value ) noexcept {
        while ( first != last ) {
            if ( *first == value ) return first;
            ++first;
        }
        return last;
    }

    template<typename T, typename pred_t>
    __forceinline T* find_if( T* first, T* last, pred_t pred ) noexcept {
        while ( first != last ) {
            if ( pred( *first ) ) return first;
            ++first;
        }
        return last;
    }

    template<typename T>
    __forceinline size_t count( const T* first, const T* last, const T& value ) noexcept {
        size_t n = 0;
        while ( first != last ) {
            if ( *first == value ) ++n;
            ++first;
        }
        return n;
    }

    template<typename T, typename pred_t>
    __forceinline size_t count_if( const T* first, const T* last, pred_t pred ) noexcept {
        size_t n = 0;
        while ( first != last ) {
            if ( pred( *first ) ) ++n;
            ++first;
        }
        return n;
    }

    template<typename T>
    __forceinline void fill( T* first, T* last, const T& value ) noexcept {
        while ( first != last ) *first++ = value;
    }

    template<typename T>
    __forceinline void fill_n( T* dst, size_t n, const T& value ) noexcept {
        while ( n-- ) *dst++ = value;
    }

    template<typename src_t, typename dst_t>
    __forceinline dst_t* copy_range( const src_t* first, const src_t* last, dst_t* dst ) noexcept {
        while ( first != last ) *dst++ = *first++;
        return dst;
    }

    template<typename src_t, typename dst_t>
    __forceinline dst_t* copy_n( const src_t* src, size_t n, dst_t* dst ) noexcept {
        while ( n-- ) *dst++ = *src++;
        return dst;
    }

    template<typename src_t, typename dst_t, typename func_t>
    __forceinline dst_t* transform( const src_t* first, const src_t* last, dst_t* dst, func_t func ) noexcept {
        while ( first != last ) *dst++ = func( *first++ );
        return dst;
    }

    template<typename T>
    __forceinline void reverse( T* first, T* last ) noexcept {
        while ( first != last && first != --last ) {
            swap( *first, *last );
            ++first;
        }
    }

    template<typename T>
    __forceinline bool equal_range( const T* first1, const T* last1, const T* first2 ) noexcept {
        while ( first1 != last1 ) {
            if ( !( *first1 == *first2 ) ) return false;
            ++first1; ++first2;
        }
        return true;
    }

    template<typename T, typename pred_t>
    __forceinline bool all_of( const T* first, const T* last, pred_t pred ) noexcept {
        while ( first != last ) {
            if ( !pred( *first ) ) return false;
            ++first;
        }
        return true;
    }

    template<typename T, typename pred_t>
    __forceinline bool any_of( const T* first, const T* last, pred_t pred ) noexcept {
        while ( first != last ) {
            if ( pred( *first ) ) return true;
            ++first;
        }
        return false;
    }

    template<typename T, typename pred_t>
    __forceinline bool none_of( const T* first, const T* last, pred_t pred ) noexcept {
        while ( first != last ) {
            if ( pred( *first ) ) return false;
            ++first;
        }
        return true;
    }

    template<typename T>
    __forceinline T sum_of( const T* first, const T* last, T init = T( ) ) noexcept {
        while ( first != last ) init = init + *first++;
        return init;
    }

    template<typename T>
    __forceinline const T* min_element( const T* first, const T* last ) noexcept {
        if ( first == last ) return last;
        const T* result = first;
        while ( ++first != last ) {
            if ( *first < *result ) result = first;
        }
        return result;
    }

    template<typename T>
    __forceinline const T* max_element( const T* first, const T* last ) noexcept {
        if ( first == last ) return last;
        const T* result = first;
        while ( ++first != last ) {
            if ( *result < *first ) result = first;
        }
        return result;
    }

    template<typename T>
    __forceinline void sort_insertion( T* first, T* last ) noexcept {
        for ( T* i = first + 1; i < last; ++i ) {
            T   key = *i;
            T* j = i;
            while ( j > first && key < *( j - 1 ) ) {
                *j = *( j - 1 );
                --j;
            }
            *j = key;
        }
    }

    template<typename T, typename compare_t>
    __forceinline void sort_insertion( T* first, T* last, compare_t cmp ) noexcept {
        for ( T* i = first + 1; i < last; ++i ) {
            T   key = *i;
            T* j = i;
            while ( j > first && cmp( key, *( j - 1 ) ) ) {
                *j = *( j - 1 );
                --j;
            }
            *j = key;
        }
    }

    template<typename T>
    __forceinline void sort( T* first, T* last ) noexcept {
        size_t n = static_cast< size_t >( last - first );
        if ( n < 2 )   return;
        if ( n <= 16 ) { sort_insertion( first, last ); return; }

        T  pivot = first[ n / 2 ];
        T* i = first;
        T* j = last - 1;

        while ( i <= j ) {
            while ( *i < pivot ) ++i;
            while ( pivot < *j ) --j;
            if ( i <= j ) { swap( *i, *j ); ++i; --j; }
        }

        if ( first < j ) sort( first, j + 1 );
        if ( i < last )  sort( i, last );
    }

    template<typename T, typename compare_t>
    __forceinline void sort( T* first, T* last, compare_t cmp ) noexcept {
        size_t n = static_cast< size_t >( last - first );
        if ( n < 2 )   return;
        if ( n <= 16 ) { sort_insertion( first, last, cmp ); return; }

        T  pivot = first[ n / 2 ];
        T* i = first;
        T* j = last - 1;

        while ( i <= j ) {
            while ( cmp( *i, pivot ) ) ++i;
            while ( cmp( pivot, *j ) ) --j;
            if ( i <= j ) { swap( *i, *j ); ++i; --j; }
        }

        if ( first < j ) sort( first, j + 1, cmp );
        if ( i < last )  sort( i, last, cmp );
    }

    template<typename T>
    __forceinline bool is_sorted( const T* first, const T* last ) noexcept {
        if ( first == last ) return true;
        const T* next = first;
        while ( ++next != last ) {
            if ( *next < *first ) return false;
            ++first;
        }
        return true;
    }

    template<typename T>
    __forceinline const T* binary_search( const T* first, const T* last, const T& value ) noexcept {
        while ( first < last ) {
            const T* mid = first + ( last - first ) / 2;
            if ( *mid < value ) first = mid + 1;
            else if ( value < *mid ) last = mid;
            else return mid;
        }
        return nullptr;
    }

    template<typename T>
    __forceinline const T* lower_bound( const T* first, const T* last, const T& value ) noexcept {
        while ( first < last ) {
            const T* mid = first + ( last - first ) / 2;
            if ( *mid < value ) first = mid + 1;
            else                last = mid;
        }
        return first;
    }

    template<typename T>
    __forceinline const T* upper_bound( const T* first, const T* last, const T& value ) noexcept {
        while ( first < last ) {
            const T* mid = first + ( last - first ) / 2;
            if ( value < *mid ) last = mid;
            else                first = mid + 1;
        }
        return first;
    }

    template<typename T>
    __forceinline T* unique( T* first, T* last ) noexcept {
        if ( first == last ) return last;
        T* result = first;
        while ( ++first != last ) {
            if ( !( *result == *first ) )
                *( ++result ) = *first;
        }
        return ++result;
    }

    template<typename T>
    __forceinline void rotate_left( T* first, T* last ) noexcept {
        if ( first == last ) return;
        T   tmp = *first;
        T* p = first;
        while ( ++p != last ) *( p - 1 ) = *p;
        *( last - 1 ) = tmp;
    }

    template<typename T>
    __forceinline void rotate_right( T* first, T* last ) noexcept {
        if ( first == last ) return;
        T   tmp = *( last - 1 );
        T* p = last - 1;
        while ( p != first ) { *p = *( p - 1 ); --p; }
        *first = tmp;
    }

    template<typename T>
    __forceinline T gcd( T a, T b ) noexcept {
        while ( b != 0 ) {
            T t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    template<typename T>
    __forceinline T lcm( T a, T b ) noexcept {
        if ( a == 0 || b == 0 ) return 0;
        return ( a / gcd( a, b ) ) * b;
    }

    template<typename T>
    __forceinline T power( T base, uint32_t exp ) noexcept {
        T result = T( 1 );
        while ( exp > 0 ) {
            if ( exp & 1 ) result = result * base;
            base = base * base;
            exp >>= 1;
        }
        return result;
    }

    template<typename T>
    __forceinline bool is_power_of_two( T v ) noexcept {
        return v > 0 && ( v & ( v - 1 ) ) == 0;
    }

    template<typename T>
    __forceinline T next_power_of_two( T v ) noexcept {
        if ( v == 0 ) return 1;
        --v;
        v |= v >> 1;
        v |= v >> 2;
        v |= v >> 4;
        if ( sizeof( T ) > 1 ) v |= v >> 8;
        if ( sizeof( T ) > 2 ) v |= v >> 16;
        if ( sizeof( T ) > 4 ) v |= v >> 32;
        return v + 1;
    }

    template<typename T>
    struct pair {
        T first;
        T second;

        constexpr pair( ) noexcept : first( ), second( ) { }
        constexpr pair( const T& a, const T& b ) noexcept : first( a ), second( b ) { }

        constexpr bool operator==( const pair& o ) const noexcept { return first == o.first && second == o.second; }
        constexpr bool operator!=( const pair& o ) const noexcept { return !( *this == o ); }
    };

    template<typename T>
    __forceinline pair<T> make_pair( const T& a, const T& b ) noexcept {
        return pair<T>( a, b );
    }

    template<typename T>
    struct minmax_result {
        T min_value;
        T max_value;
    };

    template<typename T>
    __forceinline minmax_result<T> minmax_element( const T* first, const T* last ) noexcept {
        minmax_result<T> r = { *first, *first };
        while ( ++first != last ) {
            if ( *first < r.min_value ) r.min_value = *first;
            if ( r.max_value < *first ) r.max_value = *first;
        }
        return r;
    }

} // namespace std