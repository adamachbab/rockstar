#pragma once

namespace std {

    using int8_t = signed char;
    using int16_t = short;
    using int32_t = int;
    using int64_t = long long;
    using uint8_t = unsigned char;
    using uint16_t = unsigned short;
    using uint32_t = unsigned int;
    using uint64_t = unsigned long long;

    using int_least8_t = signed char;
    using int_least16_t = short;
    using int_least32_t = int;
    using int_least64_t = long long;
    using uint_least8_t = unsigned char;
    using uint_least16_t = unsigned short;
    using uint_least32_t = unsigned int;
    using uint_least64_t = unsigned long long;

    using int_fast8_t = signed char;
    using int_fast16_t = int;
    using int_fast32_t = int;
    using int_fast64_t = long long;
    using uint_fast8_t = unsigned char;
    using uint_fast16_t = unsigned int;
    using uint_fast32_t = unsigned int;
    using uint_fast64_t = unsigned long long;

    using intptr_t = long long;
    using uintptr_t = unsigned long long;
    using size_t = unsigned long long;
    using ssize_t = long long;
    using intmax_t = long long;
    using uintmax_t = unsigned long long;
    using ptrdiff_t = long long;
    using max_align_t = long double;
    using byte_t = unsigned char;

    using wchar_alias = unsigned short;
    using char8_alias = unsigned char;
    using char16_alias = unsigned short;
    using char32_alias = unsigned int;

    using double_t = double;
    using float_t = float;

    constexpr int8_t   int8_min = -127 - 1;
    constexpr int8_t   int8_max = 127;
    constexpr int16_t  int16_min = -32767 - 1;
    constexpr int16_t  int16_max = 32767;
    constexpr int32_t  int32_min = -2147483647 - 1;
    constexpr int32_t  int32_max = 2147483647;
    constexpr int64_t  int64_min = -9223372036854775807LL - 1;
    constexpr int64_t  int64_max = 9223372036854775807LL;

    constexpr uint8_t  uint8_max = 0xFFu;
    constexpr uint16_t uint16_max = 0xFFFFu;
    constexpr uint32_t uint32_max = 0xFFFFFFFFu;
    constexpr uint64_t uint64_max = 0xFFFFFFFFFFFFFFFFull;

    constexpr size_t    size_max = uint64_max;
    constexpr ptrdiff_t ptrdiff_min = int64_min;
    constexpr ptrdiff_t ptrdiff_max = int64_max;
    constexpr intmax_t  intmax_min = int64_min;
    constexpr intmax_t  intmax_max = int64_max;
    constexpr uintmax_t uintmax_max = uint64_max;
    constexpr uintptr_t uintptr_max = uint64_max;

    constexpr size_t bits_per_byte = 8;
    constexpr size_t int8_bits = 8;
    constexpr size_t int16_bits = 16;
    constexpr size_t int32_bits = 32;
    constexpr size_t int64_bits = 64;
    constexpr size_t int128_bits = 128;

    struct m128a_t { uint64_t m_low; int64_t  m_high; };
    struct m128i_t { uint64_t m_low; uint64_t m_high; };
    struct m128_t { float    m_data[ 4 ]; };
    struct m128d_t { double   m_data[ 2 ]; };
    struct m256i_t { uint64_t m_data[ 4 ]; };
    struct m512i_t { uint64_t m_data[ 8 ]; };

    struct uint128_t {
        uint64_t m_low;
        uint64_t m_high;

        constexpr uint128_t( ) noexcept : m_low( 0 ), m_high( 0 ) { }
        constexpr uint128_t( uint64_t low ) noexcept : m_low( low ), m_high( 0 ) { }
        constexpr uint128_t( uint64_t low, uint64_t high ) noexcept : m_low( low ), m_high( high ) { }

        constexpr uint128_t( int value ) noexcept
            : m_low( static_cast< uint64_t >( value ) ),
            m_high( value < 0 ? uint64_max : 0 ) {
        }

        constexpr uint128_t( long long value ) noexcept
            : m_low( static_cast< uint64_t >( value ) ),
            m_high( value < 0 ? uint64_max : 0 ) {
        }

        constexpr bool operator==( const uint128_t& o ) const noexcept { return m_low == o.m_low && m_high == o.m_high; }
        constexpr bool operator!=( const uint128_t& o ) const noexcept { return !( *this == o ); }
        constexpr bool operator<( const uint128_t& o ) const noexcept { return m_high < o.m_high || ( m_high == o.m_high && m_low < o.m_low ); }
        constexpr bool operator>( const uint128_t& o ) const noexcept { return o < *this; }
        constexpr bool operator<=( const uint128_t& o ) const noexcept { return !( o < *this ); }
        constexpr bool operator>=( const uint128_t& o ) const noexcept { return !( *this < o ); }

        constexpr explicit operator bool( )    const noexcept { return m_low != 0 || m_high != 0; }
        constexpr explicit operator uint64_t( ) const noexcept { return m_low; }
        constexpr explicit operator uint32_t( ) const noexcept { return static_cast< uint32_t >( m_low ); }
        constexpr explicit operator uint16_t( ) const noexcept { return static_cast< uint16_t >( m_low ); }
        constexpr explicit operator uint8_t( )  const noexcept { return static_cast< uint8_t >( m_low ); }

        uint128_t& operator=( uint64_t value ) noexcept { m_low = value; m_high = 0; return *this; }

        constexpr uint128_t operator~( ) const noexcept { return uint128_t( ~m_low, ~m_high ); }
        constexpr uint128_t operator-( ) const noexcept { return uint128_t( 0 ) - *this; }

        constexpr uint128_t operator+( const uint128_t& o ) const noexcept {
            uint64_t lo = m_low + o.m_low;
            uint64_t carry = ( lo < m_low ) ? 1 : 0;
            return uint128_t( lo, m_high + o.m_high + carry );
        }

        constexpr uint128_t operator-( const uint128_t& o ) const noexcept {
            uint64_t lo = m_low - o.m_low;
            uint64_t borrow = ( m_low < o.m_low ) ? 1 : 0;
            return uint128_t( lo, m_high - o.m_high - borrow );
        }

        constexpr uint128_t operator&( const uint128_t& o ) const noexcept { return uint128_t( m_low & o.m_low, m_high & o.m_high ); }
        constexpr uint128_t operator|( const uint128_t& o ) const noexcept { return uint128_t( m_low | o.m_low, m_high | o.m_high ); }
        constexpr uint128_t operator^( const uint128_t& o ) const noexcept { return uint128_t( m_low ^ o.m_low, m_high ^ o.m_high ); }

        constexpr uint128_t operator<<( unsigned int shift ) const noexcept {
            if ( shift == 0 )   return *this;
            if ( shift >= 128 ) return uint128_t( 0, 0 );
            if ( shift >= 64 )  return uint128_t( 0, m_low << ( shift - 64 ) );
            return uint128_t( m_low << shift, ( m_high << shift ) | ( m_low >> ( 64 - shift ) ) );
        }

        constexpr uint128_t operator>>( unsigned int shift ) const noexcept {
            if ( shift == 0 )   return *this;
            if ( shift >= 128 ) return uint128_t( 0, 0 );
            if ( shift >= 64 )  return uint128_t( m_high >> ( shift - 64 ), 0 );
            return uint128_t( ( m_low >> shift ) | ( m_high << ( 64 - shift ) ), m_high >> shift );
        }

        uint128_t& operator+=( const uint128_t& o )   noexcept { return *this = *this + o; }
        uint128_t& operator-=( const uint128_t& o )   noexcept { return *this = *this - o; }
        uint128_t& operator&=( const uint128_t& o )   noexcept { return *this = *this & o; }
        uint128_t& operator|=( const uint128_t& o )   noexcept { return *this = *this | o; }
        uint128_t& operator^=( const uint128_t& o )   noexcept { return *this = *this ^ o; }
        uint128_t& operator<<=( unsigned int s )      noexcept { return *this = *this << s; }
        uint128_t& operator>>=( unsigned int s )      noexcept { return *this = *this >> s; }

        uint128_t& operator++( )    noexcept { *this = *this + uint128_t( 1 ); return *this; }
        uint128_t& operator--( )    noexcept { *this = *this - uint128_t( 1 ); return *this; }
        uint128_t  operator++( int ) noexcept { uint128_t t = *this; ++( *this ); return t; }
        uint128_t  operator--( int ) noexcept { uint128_t t = *this; --( *this ); return t; }
    };

    struct int128_t {
        uint64_t m_low;
        int64_t  m_high;

        constexpr int128_t( ) noexcept : m_low( 0 ), m_high( 0 ) { }

        constexpr int128_t( int64_t value ) noexcept
            : m_low( static_cast< uint64_t >( value ) ),
            m_high( value < 0 ? -1 : 0 ) {
        }

        constexpr int128_t( uint64_t low, int64_t high ) noexcept
            : m_low( low ), m_high( high ) {
        }

        constexpr bool operator==( const int128_t& o ) const noexcept { return m_low == o.m_low && m_high == o.m_high; }
        constexpr bool operator!=( const int128_t& o ) const noexcept { return !( *this == o ); }
        constexpr bool operator<( const int128_t& o )  const noexcept { return m_high < o.m_high || ( m_high == o.m_high && m_low < o.m_low ); }
        constexpr bool operator>( const int128_t& o )  const noexcept { return o < *this; }
        constexpr bool operator<=( const int128_t& o ) const noexcept { return !( o < *this ); }
        constexpr bool operator>=( const int128_t& o ) const noexcept { return !( *this < o ); }

        constexpr explicit operator bool( )     const noexcept { return m_low != 0 || m_high != 0; }
        constexpr explicit operator int64_t( )  const noexcept { return static_cast< int64_t >( m_low ); }
    };

    template <class T> struct remove_reference { using type = T; };
    template <class T> struct remove_reference<T&> { using type = T; };
    template <class T> struct remove_reference<T&&> { using type = T; };
    template <class T> using  remove_reference_t = typename remove_reference<T>::type;

    template <class T> struct remove_const { using type = T; };
    template <class T> struct remove_const<const T> { using type = T; };
    template <class T> using  remove_const_t = typename remove_const<T>::type;

    template<class T, class U> struct is_same_type { static constexpr bool value = false; };
    template<class T>          struct is_same_type<T, T> { static constexpr bool value = true; };

    template<typename T> struct is_signed { static constexpr bool value = false; };
    template<> struct is_signed<int8_t> { static constexpr bool value = true; };
    template<> struct is_signed<int16_t> { static constexpr bool value = true; };
    template<> struct is_signed<int32_t> { static constexpr bool value = true; };
    template<> struct is_signed<int64_t> { static constexpr bool value = true; };
    template<> struct is_signed<float> { static constexpr bool value = true; };
    template<> struct is_signed<double> { static constexpr bool value = true; };
    template<> struct is_signed<long double> { static constexpr bool value = true; };
    template<> struct is_signed<int128_t> { static constexpr bool value = true; };

    template<typename T> struct is_unsigned { static constexpr bool value = false; };
    template<> struct is_unsigned<uint8_t> { static constexpr bool value = true; };
    template<> struct is_unsigned<uint16_t> { static constexpr bool value = true; };
    template<> struct is_unsigned<uint32_t> { static constexpr bool value = true; };
    template<> struct is_unsigned<uint64_t> { static constexpr bool value = true; };
    template<> struct is_unsigned<uint128_t> { static constexpr bool value = true; };

    template<typename T> struct is_integer { static constexpr bool value = false; };
    template<> struct is_integer<int8_t> { static constexpr bool value = true; };
    template<> struct is_integer<int16_t> { static constexpr bool value = true; };
    template<> struct is_integer<int32_t> { static constexpr bool value = true; };
    template<> struct is_integer<int64_t> { static constexpr bool value = true; };
    template<> struct is_integer<uint8_t> { static constexpr bool value = true; };
    template<> struct is_integer<uint16_t> { static constexpr bool value = true; };
    template<> struct is_integer<uint32_t> { static constexpr bool value = true; };
    template<> struct is_integer<uint64_t> { static constexpr bool value = true; };
    template<> struct is_integer<int128_t> { static constexpr bool value = true; };
    template<> struct is_integer<uint128_t> { static constexpr bool value = true; };

    template<typename T> struct is_floating_point { static constexpr bool value = false; };
    template<> struct is_floating_point<float> { static constexpr bool value = true; };
    template<> struct is_floating_point<double> { static constexpr bool value = true; };
    template<> struct is_floating_point<long double> { static constexpr bool value = true; };

    template<typename T> struct make_unsigned { using type = T; };
    template<> struct make_unsigned<int8_t> { using type = uint8_t; };
    template<> struct make_unsigned<int16_t> { using type = uint16_t; };
    template<> struct make_unsigned<int32_t> { using type = uint32_t; };
    template<> struct make_unsigned<int64_t> { using type = uint64_t; };
    template<> struct make_unsigned<int128_t> { using type = uint128_t; };

    template<typename T> struct make_signed { using type = T; };
    template<> struct make_signed<uint8_t> { using type = int8_t; };
    template<> struct make_signed<uint16_t> { using type = int16_t; };
    template<> struct make_signed<uint32_t> { using type = int32_t; };
    template<> struct make_signed<uint64_t> { using type = int64_t; };
    template<> struct make_signed<uint128_t> { using type = int128_t; };

    template<typename T> struct type_size { static constexpr size_t value = sizeof( T ); };
    template<typename T> struct type_bits { static constexpr size_t value = sizeof( T ) * 8; };

    template<size_t n> struct int_of_size;
    template<> struct int_of_size<1> { using type = int8_t;  using utype = uint8_t; };
    template<> struct int_of_size<2> { using type = int16_t; using utype = uint16_t; };
    template<> struct int_of_size<4> { using type = int32_t; using utype = uint32_t; };
    template<> struct int_of_size<8> { using type = int64_t; using utype = uint64_t; };

    template<typename T> struct type_limits;

    template<> struct type_limits<int8_t> {
        static constexpr int8_t min_value = int8_min;
        static constexpr int8_t max_value = int8_max;
        static constexpr size_t bits = 8;
        static constexpr bool   is_signed = true;
    };

    template<> struct type_limits<int16_t> {
        static constexpr int16_t min_value = int16_min;
        static constexpr int16_t max_value = int16_max;
        static constexpr size_t  bits = 16;
        static constexpr bool    is_signed = true;
    };

    template<> struct type_limits<int32_t> {
        static constexpr int32_t min_value = int32_min;
        static constexpr int32_t max_value = int32_max;
        static constexpr size_t  bits = 32;
        static constexpr bool    is_signed = true;
    };

    template<> struct type_limits<int64_t> {
        static constexpr int64_t min_value = int64_min;
        static constexpr int64_t max_value = int64_max;
        static constexpr size_t  bits = 64;
        static constexpr bool    is_signed = true;
    };

    template<> struct type_limits<uint8_t> {
        static constexpr uint8_t min_value = 0;
        static constexpr uint8_t max_value = uint8_max;
        static constexpr size_t  bits = 8;
        static constexpr bool    is_signed = false;
    };

    template<> struct type_limits<uint16_t> {
        static constexpr uint16_t min_value = 0;
        static constexpr uint16_t max_value = uint16_max;
        static constexpr size_t   bits = 16;
        static constexpr bool     is_signed = false;
    };

    template<> struct type_limits<uint32_t> {
        static constexpr uint32_t min_value = 0;
        static constexpr uint32_t max_value = uint32_max;
        static constexpr size_t   bits = 32;
        static constexpr bool     is_signed = false;
    };

    template<> struct type_limits<uint64_t> {
        static constexpr uint64_t min_value = 0;
        static constexpr uint64_t max_value = uint64_max;
        static constexpr size_t   bits = 64;
        static constexpr bool     is_signed = false;
    };

    template<typename T> constexpr T type_min( ) noexcept { return type_limits<T>::min_value; }
    template<typename T> constexpr T type_max( ) noexcept { return type_limits<T>::max_value; }

    constexpr bool is_little_endian( ) noexcept {
#if defined(_WIN32) || defined(_WIN64) || defined(__x86_64__) || defined(__i386__) || defined(__aarch64__)
        return true;
#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
        return true;
#else
        return false;
#endif
    }

    constexpr bool   is_big_endian( ) noexcept { return !is_little_endian( ); }
    constexpr size_t is_64bit_arch( ) noexcept { return sizeof( void* ) == 8; }

} // namespace std