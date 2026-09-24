#pragma once

extern "C" {
    long _InterlockedOr( long volatile*, long );
    long _InterlockedAnd( long volatile*, long );
    long _InterlockedXor( long volatile*, long );
    long _InterlockedExchange( long volatile*, long );
    long _InterlockedExchangeAdd( long volatile*, long );
    long _InterlockedCompareExchange( long volatile*, long, long );
    long _InterlockedIncrement( long volatile* );
    long _InterlockedDecrement( long volatile* );

    __int64 _InterlockedOr64( __int64 volatile*, __int64 );
    __int64 _InterlockedAnd64( __int64 volatile*, __int64 );
    __int64 _InterlockedXor64( __int64 volatile*, __int64 );
    __int64 _InterlockedExchange64( __int64 volatile*, __int64 );
    __int64 _InterlockedExchangeAdd64( __int64 volatile*, __int64 );
    __int64 _InterlockedCompareExchange64( __int64 volatile*, __int64, __int64 );
    __int64 _InterlockedIncrement64( __int64 volatile* );
    __int64 _InterlockedDecrement64( __int64 volatile* );

    unsigned char _interlockedbittestandset( long volatile*, long );
    unsigned char _interlockedbittestandreset( long volatile*, long );
    unsigned char _bittest( long const*, long );
    unsigned char _bittestandset( long*, long );
    unsigned char _bittestandreset( long*, long );

    unsigned char _interlockedbittestandset64( __int64 volatile*, __int64 );
    unsigned char _interlockedbittestandreset64( __int64 volatile*, __int64 );
    unsigned char _bittest64( __int64 const*, __int64 );
    unsigned char _bittestandset64( __int64*, __int64 );
    unsigned char _bittestandreset64( __int64*, __int64 );

    void _mm_pause( void );
    void _mm_mfence( void );
    void _mm_sfence( void );
    void _mm_lfence( void );

    void __faststorefence( void );
    void __invlpg( void* );

    unsigned __int64 __readmsr( unsigned long );
    void             __writemsr( unsigned long, unsigned __int64 );

    unsigned __int64 __readcr0( void );
    unsigned __int64 __readcr2( void );
    unsigned __int64 __readcr3( void );
    unsigned __int64 __readcr4( void );
    unsigned __int64 __readcr8( void );

    void __writecr0( unsigned __int64 );
    void __writecr3( unsigned __int64 );
    void __writecr4( unsigned __int64 );
    void __writecr8( unsigned __int64 );

    unsigned __int64 __readgsqword( unsigned long );
    unsigned long    __readgsdword( unsigned long );
    unsigned short   __readgsword( unsigned long );
    unsigned char    __readgsbyte( unsigned long );

    void __cpuid( int[ 4 ], int );
    void __cpuidex( int[ 4 ], int, int );

    unsigned __int64 __rdtsc( void );
    unsigned __int64 __rdtscp( unsigned int* );

    unsigned __int64 __readeflags( void );
    void __writeeflags( unsigned __int64 );

    void _disable( void );
    void _enable( void );
}

#pragma intrinsic( _InterlockedOr, _InterlockedAnd, _InterlockedXor )
#pragma intrinsic( _InterlockedExchange, _InterlockedExchangeAdd, _InterlockedCompareExchange )
#pragma intrinsic( _InterlockedIncrement, _InterlockedDecrement )
#pragma intrinsic( _InterlockedOr64, _InterlockedAnd64, _InterlockedXor64 )
#pragma intrinsic( _InterlockedExchange64, _InterlockedExchangeAdd64, _InterlockedCompareExchange64 )
#pragma intrinsic( _InterlockedIncrement64, _InterlockedDecrement64 )
#pragma intrinsic( _interlockedbittestandset, _interlockedbittestandreset )
#pragma intrinsic( _bittest, _bittestandset, _bittestandreset )
#pragma intrinsic( _interlockedbittestandset64, _interlockedbittestandreset64 )
#pragma intrinsic( _bittest64, _bittestandset64, _bittestandreset64 )
#pragma intrinsic( _mm_pause, _mm_mfence, _mm_sfence, _mm_lfence )
#pragma intrinsic( __faststorefence )
#pragma intrinsic( __readmsr, __writemsr )
#pragma intrinsic( __readcr0, __readcr2, __readcr3, __readcr4, __readcr8 )
#pragma intrinsic( __writecr0, __writecr3, __writecr4, __writecr8 )
#pragma intrinsic( __readgsqword, __readgsdword, __readgsword, __readgsbyte )
#pragma intrinsic( __cpuid, __cpuidex )
#pragma intrinsic( __rdtsc, __rdtscp )
#pragma intrinsic( __readeflags, __writeeflags )
#pragma intrinsic( _disable, _enable )

namespace intrin {

    __forceinline long interlocked_or( volatile long* dst, long v )           noexcept { return _InterlockedOr( dst, v ); }
    __forceinline long interlocked_and( volatile long* dst, long v )          noexcept { return _InterlockedAnd( dst, v ); }
    __forceinline long interlocked_xor( volatile long* dst, long v )          noexcept { return _InterlockedXor( dst, v ); }
    __forceinline long interlocked_exchange( volatile long* dst, long v )     noexcept { return _InterlockedExchange( dst, v ); }
    __forceinline long interlocked_exchange_add( volatile long* dst, long v ) noexcept { return _InterlockedExchangeAdd( dst, v ); }
    __forceinline long interlocked_compare_exchange( volatile long* dst, long ex, long cmp ) noexcept {
        return _InterlockedCompareExchange( dst, ex, cmp );
    }
    __forceinline long interlocked_increment( volatile long* v ) noexcept { return _InterlockedIncrement( v ); }
    __forceinline long interlocked_decrement( volatile long* v ) noexcept { return _InterlockedDecrement( v ); }

    __forceinline __int64 interlocked_or64( volatile __int64* dst, __int64 v )           noexcept { return _InterlockedOr64( dst, v ); }
    __forceinline __int64 interlocked_and64( volatile __int64* dst, __int64 v )          noexcept { return _InterlockedAnd64( dst, v ); }
    __forceinline __int64 interlocked_xor64( volatile __int64* dst, __int64 v )          noexcept { return _InterlockedXor64( dst, v ); }
    __forceinline __int64 interlocked_exchange64( volatile __int64* dst, __int64 v )     noexcept { return _InterlockedExchange64( dst, v ); }
    __forceinline __int64 interlocked_exchange_add64( volatile __int64* dst, __int64 v ) noexcept { return _InterlockedExchangeAdd64( dst, v ); }
    __forceinline __int64 interlocked_compare_exchange64( volatile __int64* dst, __int64 ex, __int64 cmp ) noexcept {
        return _InterlockedCompareExchange64( dst, ex, cmp );
    }
    __forceinline __int64 interlocked_increment64( volatile __int64* v ) noexcept { return _InterlockedIncrement64( v ); }
    __forceinline __int64 interlocked_decrement64( volatile __int64* v ) noexcept { return _InterlockedDecrement64( v ); }

    __forceinline unsigned char bit_test_and_set( volatile long* base, long bit )   noexcept { return _interlockedbittestandset( base, bit ); }
    __forceinline unsigned char bit_test_and_reset( volatile long* base, long bit ) noexcept { return _interlockedbittestandreset( base, bit ); }
    __forceinline unsigned char bit_test( const long* base, long bit )              noexcept { return _bittest( base, bit ); }
    __forceinline unsigned char bit_set( long* base, long bit )                     noexcept { return _bittestandset( base, bit ); }
    __forceinline unsigned char bit_reset( long* base, long bit )                   noexcept { return _bittestandreset( base, bit ); }

    __forceinline unsigned char bit_test_and_set64( volatile __int64* base, __int64 bit )   noexcept { return _interlockedbittestandset64( base, bit ); }
    __forceinline unsigned char bit_test_and_reset64( volatile __int64* base, __int64 bit ) noexcept { return _interlockedbittestandreset64( base, bit ); }
    __forceinline unsigned char bit_test64( const __int64* base, __int64 bit )              noexcept { return _bittest64( base, bit ); }
    __forceinline unsigned char bit_set64( __int64* base, __int64 bit )                     noexcept { return _bittestandset64( base, bit ); }
    __forceinline unsigned char bit_reset64( __int64* base, __int64 bit )                   noexcept { return _bittestandreset64( base, bit ); }

    __forceinline void cpu_pause( )                     noexcept { _mm_pause( ); }
    __forceinline void mem_fence( )                     noexcept { _mm_mfence( ); }
    __forceinline void store_fence( )                   noexcept { _mm_sfence( ); }
    __forceinline void load_fence( )                    noexcept { _mm_lfence( ); }
    __forceinline void fast_store_fence( )              noexcept { __faststorefence( ); }
    __forceinline void invalidate_page( void* addr )    noexcept { __invlpg( addr ); }

    __forceinline unsigned __int64 read_msr( unsigned long msr )                       noexcept { return __readmsr( msr ); }
    __forceinline void             write_msr( unsigned long msr, unsigned __int64 v )  noexcept { __writemsr( msr, v ); }

    __forceinline unsigned __int64 read_cr0( ) noexcept { return __readcr0( ); }
    __forceinline unsigned __int64 read_cr2( ) noexcept { return __readcr2( ); }
    __forceinline unsigned __int64 read_cr3( ) noexcept { return __readcr3( ); }
    __forceinline unsigned __int64 read_cr4( ) noexcept { return __readcr4( ); }
    __forceinline unsigned __int64 read_cr8( ) noexcept { return __readcr8( ); }

    __forceinline void write_cr0( unsigned __int64 v ) noexcept { __writecr0( v ); }
    __forceinline void write_cr3( unsigned __int64 v ) noexcept { __writecr3( v ); }
    __forceinline void write_cr4( unsigned __int64 v ) noexcept { __writecr4( v ); }
    __forceinline void write_cr8( unsigned __int64 v ) noexcept { __writecr8( v ); }

    __forceinline unsigned __int64 read_gs_qword( unsigned long offset ) noexcept { return __readgsqword( offset ); }
    __forceinline unsigned long    read_gs_dword( unsigned long offset ) noexcept { return __readgsdword( offset ); }
    __forceinline unsigned short   read_gs_word( unsigned long offset )  noexcept { return __readgsword( offset ); }
    __forceinline unsigned char    read_gs_byte( unsigned long offset )  noexcept { return __readgsbyte( offset ); }

    __forceinline void cpuid( int info[ 4 ], int fn )              noexcept { __cpuid( info, fn ); }
    __forceinline void cpuid_ex( int info[ 4 ], int fn, int sub )  noexcept { __cpuidex( info, fn, sub ); }

    __forceinline unsigned __int64 read_tsc( )                        noexcept { return __rdtsc( ); }
    __forceinline unsigned __int64 read_tscp( unsigned int* aux )     noexcept { return __rdtscp( aux ); }

    __forceinline void disable_interrupts( ) noexcept { _disable( ); }
    __forceinline void enable_interrupts( )  noexcept { _enable( ); }

} // namespace intrin