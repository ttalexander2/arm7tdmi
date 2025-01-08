//
// Created by Thomas Alexander on 9/14/24.
//
#pragma once

#include <arm7tdmi/common.h>
#include <arm7tdmi/util.h>

#include <fmt/format.h>

namespace arm7tdmi {

    enum class Register
    {
        R0  = 0x0,
        R1  = 0x1,
        R2  = 0x2,
        R3  = 0x3,
        R4  = 0x4,
        R5  = 0x5,
        R6  = 0x6,
        R7  = 0x7,
        R8  = 0x8,
        R9  = 0x9,
        R10 = 0xA,
        R11 = 0xB,
        R12 = 0xC,
        R13 = 0xD,
        SP = R13,
        R14 = 0xE,
        LR = R14,
        R15 = 0xF,
        PC = R15,
        CPSR = 0x10,
        SPSR = 0x11
    };

    static constexpr size_t REG_R0 = 0x0;
    static constexpr size_t REG_R1 = 0x1;
    static constexpr size_t REG_R2 = 0x2;
    static constexpr size_t REG_R3 = 0x3;
    static constexpr size_t REG_R4 = 0x4;
    static constexpr size_t REG_R5 = 0x5;
    static constexpr size_t REG_R6 = 0x6;
    static constexpr size_t REG_R7 = 0x7;
    static constexpr size_t REG_R8 = 0x8;
    static constexpr size_t REG_R9 = 0x9;
    static constexpr size_t REG_R10 = 0xA;
    static constexpr size_t REG_R11 = 0xB;
    static constexpr size_t REG_R12 = 0xC;
    static constexpr size_t REG_R13 = 0xD;
    static constexpr size_t REG_R14 = 0xE;
    static constexpr size_t REG_R15 = 0xF;

    static constexpr size_t REG_CPSR = 0x10;

    static constexpr size_t REG_R8_FIQ = 0x11;
    static constexpr size_t REG_R9_FIQ = 0x12;
    static constexpr size_t REG_R10_FIQ = 0x13;
    static constexpr size_t REG_R11_FIQ = 0x14;
    static constexpr size_t REG_R12_FIQ = 0x15;
    static constexpr size_t REG_R13_FIQ = 0x16;
    static constexpr size_t REG_R14_FIQ = 0x17;
    static constexpr size_t REG_SPSR_FIQ = 0x18;

    static constexpr size_t REG_R13_SVC = 0x19;
    static constexpr size_t REG_R14_SVC = 0x1A;
    static constexpr size_t REG_SPSR_SVC = 0x1B;

    static constexpr size_t REG_R13_ABT = 0x1C;
    static constexpr size_t REG_R14_ABT = 0x1D;
    static constexpr size_t REG_SPSR_ABT = 0x1E;

    static constexpr size_t REG_R13_IRQ = 0x1F;
    static constexpr size_t REG_R14_IRQ = 0x20;
    static constexpr size_t REG_SPSR_IRQ = 0x21;

    static constexpr size_t REG_R13_UNDEF = 0x22;
    static constexpr size_t REG_R14_UNDEF = 0x23;
    static constexpr size_t REG_SPSR_UNDEF = 0x24;

    static constexpr u32 CPSR_N = 31u;
    static constexpr u32 CPSR_Z = 30u;
    static constexpr u32 CPSR_C = 29u;
    static constexpr u32 CPSR_V = 28u;
    static constexpr u32 CPSR_Q = 27u;
    static constexpr u32 CPSR_I = 7u;
    static constexpr u32 CPSR_F = 6u;
    static constexpr u32 CPSR_T = 5u;
    static constexpr u32 CPSR_M = 0x1f;

    class cpu_registers {
    public:

        u32 data[37] = {};

        [[nodiscard]] inline u32 get(const Register reg) const { return data[register_enum_to_index(reg)];}
        [[nodiscard]] inline u32 get(u32 reg) const { return get(static_cast<Register>(reg)); }

        inline void set(const Register reg, const u32 val) { data[register_enum_to_index(reg)] = val; }
        inline void set(u32 reg, const u32 val) { set(static_cast<Register>(reg), val); }

        [[nodiscard]] bool cpsr_get_n() const;
        void cpsr_set_n(bool value);

        [[nodiscard]] bool cpsr_get_z() const;
        void cpsr_set_z(bool value);

        [[nodiscard]] bool cpsr_get_c() const;
        void cpsr_set_c(bool value);

        [[nodiscard]] bool cpsr_get_v() const;
        void cpsr_set_v(bool value);

        [[nodiscard]] bool cpsr_get_q() const;
        void cpsr_set_q(bool value);

        [[nodiscard]] bool cpsr_get_i() const;
        void cpsr_set_i(bool value);

        [[nodiscard]] bool cpsr_get_f() const;
        void cpsr_set_f(bool value);

        [[nodiscard]] bool cpsr_get_t() const;
        void cpsr_set_t(bool value);

        [[nodiscard]] u32 cpsr_get_m() const;
        void cpsr_set_m(u32 m);

        [[nodiscard]] cpu_mode cpsr_get_mode() const;
        void cpsr_set_mode(cpu_mode mode);

        [[nodiscard]] size_t register_enum_to_index(Register reg) const;
        [[nodiscard]] static Register register_index_to_enum(size_t index);

        [[nodiscard]] inline u32 r0() const { return get(Register::R0); }
        inline void r0(const u32 val) { set(Register::R0, val); }

        [[nodiscard]] inline u32 r1() const { return get(Register::R1); }
        inline void r1(const u32 val) { set(Register::R1, val); }

        [[nodiscard]] inline u32 r2() const { return get(Register::R2); }
        inline void r2(const u32 val) { set(Register::R2, val); }

        [[nodiscard]] inline u32 r3() const { return get(Register::R3); }
        inline void r3(const u32 val) { set(Register::R3, val); }

        [[nodiscard]] inline u32 r4() const { return get(Register::R4); }
        inline void r4(const u32 val) { set(Register::R4, val); }

        [[nodiscard]] inline u32 r5() const { return get(Register::R5); }
        inline void r5(const u32 val) { set(Register::R5, val); }

        [[nodiscard]] inline u32 r6() const { return get(Register::R6); }
        inline void r6(const u32 val) { set(Register::R6, val); }

        [[nodiscard]] inline u32 r7() const { return get(Register::R7); }
        inline void r7(const u32 val) { set(Register::R7, val); }

        [[nodiscard]] inline u32 r8() const { return get(Register::R8); }
        inline void r8(const u32 val) { set(Register::R8, val); }

        [[nodiscard]] inline u32 r9() const { return get(Register::R9); }
        inline void r9(const u32 val) { set(Register::R9, val); }

        [[nodiscard]] inline u32 r10() const { return get(Register::R10); }
        inline void r10(const u32 val) { set(Register::R10, val); }

        [[nodiscard]] inline u32 r11() const { return get(Register::R11); }
        inline void r11(const u32 val) { set(Register::R11, val); }

        [[nodiscard]] inline u32 r12() const { return get(Register::R12); }
        inline void r12(const u32 val) { set(Register::R12, val); }

        [[nodiscard]] inline u32 r13() const { return get(Register::R13); }
        inline void r13(const u32 val) { set(Register::R13, val); }

        [[nodiscard]] inline u32 r14() const { return get(Register::R14); }
        inline void r14(const u32 val) { set(Register::R14, val); }

        [[nodiscard]] inline u32 r15() const { return get(Register::R15); }
        inline void r15(const u32 val) { set(Register::R15, val); }

        [[nodiscard]] inline u32 sp() const { return r13(); }
        inline void sp(const u32 val) { r13(val); }

        [[nodiscard]] inline u32 lr() const { return r14(); }
        inline void lr(const u32 val) { r14(val); }

        [[nodiscard]] inline u32 pc() const { return r15(); }
        inline void pc(const u32 val) { r15(val); }

        [[nodiscard]] inline u32 cpsr() const { return get(Register::CPSR); }
        inline void cpsr(const u32 val) { set(Register::CPSR, val); }

        [[nodiscard]] inline u32 spsr() const { return get(Register::SPSR); }
        inline void spsr(const u32 val) { set(Register::SPSR, val); }
    };

}