#pragma once

namespace kernel::api::kdp {

    __forceinline void* debug_routine_select( ) noexcept {
        const auto addr = symbols::get( ).m_kdp.m_debug_routine_select;
        return addr ? reinterpret_cast< void* >( addr ) : nullptr;
    }

    __forceinline std::uint64_t trap( ) noexcept {
        return symbols::get( ).m_kdp.m_trap;
    }

    __forceinline std::uint64_t report( ) noexcept {
        return symbols::get( ).m_kdp.m_report;
    }

    __forceinline std::uint64_t stub( ) noexcept {
        return symbols::get( ).m_kdp.m_stub;
    }

} // namespace kernel::api::kdp