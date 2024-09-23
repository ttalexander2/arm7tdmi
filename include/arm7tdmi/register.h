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

        inline void set_bit(const u32 n, const bool value) { data = util::bit_set_to(data, n, value);};
        [[nodiscard]] inline bool get_bit(const u32 n) const { return util::bit_check(data, n); }
        inline void flip_bit(const u32 n) { data = util::bit_toggle(data, n); }
        inline void reset_bit(const u32 n) { data = util::bit_set_to(data, n, false); }

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

        [[nodiscard]] inline bool get_n() const { return this->get_bit(CPSR_N); }
        [[nodiscard]] inline bool get_z() const { return this->get_bit(CPSR_Z); }
        [[nodiscard]] inline bool get_c() const { return this->get_bit(CPSR_C); }
        [[nodiscard]] inline bool get_v() const { return this->get_bit(CPSR_V); }
        [[nodiscard]] inline bool get_q() const { return this->get_bit(CPSR_Q); }
        [[nodiscard]] inline bool get_i() const { return this->get_bit(CPSR_I); }
        [[nodiscard]] inline bool get_f() const { return this->get_bit(CPSR_F); }
        [[nodiscard]] inline bool get_t() const { return this->get_bit(CPSR_T); }
        [[nodiscard]] inline bool get_m4() const { return this->get_bit(CPSR_M4); }
        [[nodiscard]] inline bool get_m3() const { return this->get_bit(CPSR_M3); }
        [[nodiscard]] inline bool get_m2() const { return this->get_bit(CPSR_M2); }
        [[nodiscard]] inline bool get_m1() const { return this->get_bit(CPSR_M1); }
        [[nodiscard]] inline bool get_m0() const { return this->get_bit(CPSR_M0); }

        inline void set_n(const bool value) { this->set_bit(CPSR_N, value); }
        inline void set_z(const bool value) { this->set_bit(CPSR_Z, value); }
        inline void set_c(const bool value) { this->set_bit(CPSR_C, value); }
        inline void set_v(const bool value) { this->set_bit(CPSR_V, value); }
        inline void set_q(const bool value) { this->set_bit(CPSR_Q, value); }
        inline void set_i(const bool value) { this->set_bit(CPSR_I, value); }
        inline void set_f(const bool value) { this->set_bit(CPSR_F, value); }
        inline void set_t(const bool value) { this->set_bit(CPSR_T, value); }
        inline void set_m4(const bool value) { this->set_bit(CPSR_M4, value); }
        inline void set_m3(const bool value) { this->set_bit(CPSR_M3, value); }
        inline void set_m2(const bool value) { this->set_bit(CPSR_M2, value); }
        inline void set_m1(const bool value) { this->set_bit(CPSR_M1, value); }
        inline void set_m0(const bool value) { this->set_bit(CPSR_M0, value); }

        // ReSharper disable once CppNonExplicitConversionOperator
        inline operator u32&() { return data;} // NOLINT(*-explicit-constructor)
        inline operator const u32&() const { return data;} // NOLINT(*-explicit-constructor)
        inline cpsr_register &operator=(const u32 value) { data = value; return *this; }
    };

    struct cpu_register_set {
        cpu_register r0;
        cpu_register r1;
        cpu_register r2;
        cpu_register r3;
        cpu_register r4;
        cpu_register r5;
        cpu_register r6;
        cpu_register r7;
        cpu_register r8;
        cpu_register r9;
        cpu_register r10;
        cpu_register r11;
        cpu_register r12;

        union {
            cpu_register r13;
            cpu_register sp;
        };

        union {
            cpu_register r14;
            cpu_register lr;
        };

        union {
            cpu_register r15;
            cpu_register pc;
        };

        cpsr_register cpsr;
        cpu_register spsr;
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