//
// Created by Thomas Alexander on 9/14/24.
//
#pragma once

#include <arm7tdmi/types.h>
#include <fmt/format.h>

#include "util.h"

namespace arm7tdmi {

    class cpu_register {
        friend struct fmt::formatter<cpu_register>;
    protected:
        u32 data = {};
    public:

        inline void set_bit(const u32 n, const bool value) { data = bit_set_to(data, n, value);};
        [[nodiscard]] inline bool get_bit(const u32 n) const { return bit_check(data, n); }
        inline void flip_bit(const u32 n) { data = bit_toggle(data, n); }
        inline void reset_bit(const u32 n) { data = bit_set_to(data, n, false); }

        // ReSharper disable once CppNonExplicitConversionOperator
        inline operator u32&() { return data;} // NOLINT(*-explicit-constructor)
        inline operator const u32&() const { return data;} // NOLINT(*-explicit-constructor)
        inline cpu_register &operator=(const u32 value) { data = value; return *this; }
    };

    static constexpr u32 CPSR_N = 31u;
    static constexpr u32 CPSR_Z = 30u;
    static constexpr u32 CPSR_C = 29u;
    static constexpr u32 CPSR_V = 28u;
    static constexpr u32 CPSR_Q = 27u;
    static constexpr u32 CPSR_I = 7u;
    static constexpr u32 CPSR_F = 6u;
    static constexpr u32 CPSR_T = 5u;
    static constexpr u32 CPSR_M4 = 4u;
    static constexpr u32 CPSR_M3 = 3u;
    static constexpr u32 CPSR_M2 = 2u;
    static constexpr u32 CPSR_M1 = 1u;
    static constexpr u32 CPSR_M0 = 0u;

    class cpsr_register : public cpu_register {
        friend struct fmt::formatter<cpu_register>;
    public:

        [[nodiscard]] constexpr inline bool get_n() const { return this->get_bit(CPSR_N); }
        [[nodiscard]] constexpr inline bool get_z() const { return this->get_bit(CPSR_Z); }
        [[nodiscard]] constexpr inline bool get_c() const { return this->get_bit(CPSR_C); }
        [[nodiscard]] constexpr inline bool get_v() const { return this->get_bit(CPSR_V); }
        [[nodiscard]] constexpr inline bool get_q() const { return this->get_bit(CPSR_Q); }
        [[nodiscard]] constexpr inline bool get_i() const { return this->get_bit(CPSR_I); }
        [[nodiscard]] constexpr inline bool get_f() const { return this->get_bit(CPSR_F); }
        [[nodiscard]] constexpr inline bool get_t() const { return this->get_bit(CPSR_T); }
        [[nodiscard]] constexpr inline bool get_m4() const { return this->get_bit(CPSR_M4); }
        [[nodiscard]] constexpr inline bool get_m3() const { return this->get_bit(CPSR_M3); }
        [[nodiscard]] constexpr inline bool get_m2() const { return this->get_bit(CPSR_M2); }
        [[nodiscard]] constexpr inline bool get_m1() const { return this->get_bit(CPSR_M1); }
        [[nodiscard]] constexpr inline bool get_m0() const { return this->get_bit(CPSR_M0); }

        constexpr inline void set_n(const bool value) { this->set_bit(CPSR_N, value); }
        constexpr inline void set_z(const bool value) { this->set_bit(CPSR_Z, value); }
        constexpr inline void set_c(const bool value) { this->set_bit(CPSR_C, value); }
        constexpr inline void set_v(const bool value) { this->set_bit(CPSR_V, value); }
        constexpr inline void set_q(const bool value) { this->set_bit(CPSR_Q, value); }
        constexpr inline void set_i(const bool value) { this->set_bit(CPSR_I, value); }
        constexpr inline void set_f(const bool value) { this->set_bit(CPSR_F, value); }
        constexpr inline void set_t(const bool value) { this->set_bit(CPSR_T, value); }
        constexpr inline void set_m4(const bool value) { this->set_bit(CPSR_M4, value); }
        constexpr inline void set_m3(const bool value) { this->set_bit(CPSR_M3, value); }
        constexpr inline void set_m2(const bool value) { this->set_bit(CPSR_M2, value); }
        constexpr inline void set_m1(const bool value) { this->set_bit(CPSR_M1, value); }
        constexpr inline void set_m0(const bool value) { this->set_bit(CPSR_M0, value); }

        // ReSharper disable once CppNonExplicitConversionOperator
        operator u32&() { return data;} // NOLINT(*-explicit-constructor)
        cpsr_register &operator=(const u32 value) { data = value; return *this; }
    };
}

template <>
struct fmt::formatter<arm7tdmi::cpu_register> : formatter<u32> {
    auto format(arm7tdmi::cpu_register const &c, format_context& ctx) const {
        return formatter<u32>::format(c.data, ctx);
    }
};

template <>
struct fmt::formatter<arm7tdmi::cpsr_register> : formatter<arm7tdmi::cpu_register> {
    auto format(arm7tdmi::cpsr_register const &c, format_context& ctx) const {
        return formatter<arm7tdmi::cpu_register>::format(c, ctx);
    }
};