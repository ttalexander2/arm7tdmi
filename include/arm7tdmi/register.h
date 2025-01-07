//
// Created by Thomas Alexander on 9/14/24.
//
#pragma once

#include <arm7tdmi/common.h>
#include <arm7tdmi/util.h>

#include <fmt/format.h>

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
        [[nodiscard]] inline u32 get_m() const { return data & 0x1F; }

        inline void set_n(const bool value) { this->set_bit(CPSR_N, value); }
        inline void set_z(const bool value) { this->set_bit(CPSR_Z, value); }
        inline void set_c(const bool value) { this->set_bit(CPSR_C, value); }
        inline void set_v(const bool value) { this->set_bit(CPSR_V, value); }
        inline void set_q(const bool value) { this->set_bit(CPSR_Q, value); }
        inline void set_i(const bool value) { this->set_bit(CPSR_I, value); }
        inline void set_f(const bool value) { this->set_bit(CPSR_F, value); }
        inline void set_t(const bool value) { this->set_bit(CPSR_T, value); }
        inline void set_m(const u32 mode) { data = (data & ~0x1F) | (mode & 0x1F); }

        [[nodiscard]] inline cpu_mode get_mode() const { return static_cast<cpu_mode>(get_m()); }
        void set_mode(cpu_mode mode) { set_m(static_cast<u32>(mode)); }

        // ReSharper disable once CppNonExplicitConversionOperator
        inline operator u32&() { return data;} // NOLINT(*-explicit-constructor)
        inline operator const u32&() const { return data;} // NOLINT(*-explicit-constructor)
        inline cpsr_register &operator=(const u32 value) { data = value; return *this; }
    };

    struct cpu_register_subset {
        cpu_register& r0;
        cpu_register& r1;
        cpu_register& r2;
        cpu_register& r3;
        cpu_register& r4;
        cpu_register& r5;
        cpu_register& r6;
        cpu_register& r7;
        cpu_register& r8;
        cpu_register& r9;
        cpu_register& r10;
        cpu_register& r11;
        cpu_register& r12;
        cpu_register& r13;
        cpu_register& r14;
        cpu_register& r15;
        cpsr_register& cpsr;
        cpu_register& spsr;

        [[nodiscard]] cpu_register& operator[](size_t index) const;

    };

    struct cpu_register_set {

        cpu_register_set();

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
            cpu_register r13{};
            cpu_register sp;
        };

        union {
            cpu_register r14{};
            cpu_register lr;
        };

        union {
            cpu_register r15{};
            cpu_register pc;
        };

        cpu_register r8_fiq;
        cpu_register r9_fiq;
        cpu_register r10_fiq;
        cpu_register r11_fiq;
        cpu_register r12_fiq;
        cpu_register r13_fiq;
        cpu_register r14_fiq;

        cpu_register r13_svc;
        cpu_register r14_svc;
        cpu_register r13_abt;
        cpu_register r14_abt;
        cpu_register r13_irq;
        cpu_register r14_irq;
        cpu_register r13_und;
        cpu_register r14_und;

        cpsr_register cpsr;

        cpu_register spsr_fiq;
        cpu_register spsr_svc;
        cpu_register spsr_abt;
        cpu_register spsr_irq;
        cpu_register spsr_und;

        [[nodiscard]] const cpu_register_subset& subset(cpu_mode mode) const;

    private:
        cpu_register_subset user_subset;
        cpu_register_subset fiq_subset;
        cpu_register_subset irq_subset;
        cpu_register_subset supervisor_subset;
        cpu_register_subset abort_subset;
        cpu_register_subset undefined_subset;
        cpu_register_subset system_subset;
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