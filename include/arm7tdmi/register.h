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

        [[nodiscard]] u32 get(const Register reg) const noexcept { return data[register_enum_to_index(reg)];}
        [[nodiscard]] u32 get(u32 reg) const noexcept { return get(static_cast<Register>(reg)); }

        void set(const Register reg, const u32 val) noexcept { data[register_enum_to_index(reg)] = val; }
        void set(u32 reg, const u32 val) noexcept { set(static_cast<Register>(reg), val); }

        [[nodiscard]] bool cpsr_get_n() const noexcept;
        void cpsr_set_n(bool value) noexcept;

        [[nodiscard]] bool cpsr_get_z() const noexcept;
        void cpsr_set_z(bool value) noexcept;

        [[nodiscard]] bool cpsr_get_c() const noexcept;
        void cpsr_set_c(bool value) noexcept;

        [[nodiscard]] bool cpsr_get_v() const noexcept;
        void cpsr_set_v(bool value) noexcept;

        [[nodiscard]] bool cpsr_get_q() const noexcept;
        void cpsr_set_q(bool value) noexcept;

        [[nodiscard]] bool cpsr_get_i() const noexcept;
        void cpsr_set_i(bool value) noexcept;

        [[nodiscard]] bool cpsr_get_f() const noexcept;
        void cpsr_set_f(bool value) noexcept;

        [[nodiscard]] bool cpsr_get_t() const noexcept;
        void cpsr_set_t(bool value) noexcept;

        [[nodiscard]] u32 cpsr_get_m() const noexcept;
        void cpsr_set_m(u32 m) noexcept;

        [[nodiscard]] cpu_mode cpsr_get_mode() const noexcept;
        void cpsr_set_mode(cpu_mode mode) noexcept;

        [[nodiscard]] size_t register_enum_to_index(Register reg) const noexcept;
        [[nodiscard]] static Register register_index_to_enum(size_t index) noexcept;

        [[nodiscard]] u32 r0() const noexcept { return get(Register::R0); }
        void r0(const u32 val) noexcept { set(Register::R0, val); }

        [[nodiscard]] u32 r1() const noexcept { return get(Register::R1); }
        void r1(const u32 val) noexcept { set(Register::R1, val); }

        [[nodiscard]] u32 r2() const noexcept { return get(Register::R2); }
        void r2(const u32 val) noexcept { set(Register::R2, val); }

        [[nodiscard]] u32 r3() const noexcept { return get(Register::R3); }
        void r3(const u32 val) noexcept { set(Register::R3, val); }

        [[nodiscard]] u32 r4() const noexcept { return get(Register::R4); }
        void r4(const u32 val) noexcept { set(Register::R4, val); }

        [[nodiscard]] u32 r5() const noexcept { return get(Register::R5); }
        void r5(const u32 val) noexcept { set(Register::R5, val); }

        [[nodiscard]] u32 r6() const noexcept { return get(Register::R6); }
        void r6(const u32 val) noexcept { set(Register::R6, val); }

        [[nodiscard]] u32 r7() const noexcept { return get(Register::R7); }
        void r7(const u32 val) noexcept { set(Register::R7, val); }

        [[nodiscard]] u32 r8() const noexcept { return get(Register::R8); }
        void r8(const u32 val) noexcept { set(Register::R8, val); }

        [[nodiscard]] u32 r9() const noexcept { return get(Register::R9); }
        void r9(const u32 val) noexcept { set(Register::R9, val); }

        [[nodiscard]] u32 r10() const noexcept { return get(Register::R10); }
        void r10(const u32 val) noexcept { set(Register::R10, val); }

        [[nodiscard]] u32 r11() const noexcept { return get(Register::R11); }
        void r11(const u32 val) noexcept { set(Register::R11, val); }

        [[nodiscard]] u32 r12() const noexcept { return get(Register::R12); }
        void r12(const u32 val) noexcept { set(Register::R12, val); }

        [[nodiscard]] u32 r13() const noexcept { return get(Register::R13); }
        void r13(const u32 val) noexcept { set(Register::R13, val); }

        [[nodiscard]] u32 r14() const noexcept { return get(Register::R14); }
        void r14(const u32 val) noexcept { set(Register::R14, val); }

        [[nodiscard]] u32 r15() const noexcept { return get(Register::R15); }
        void r15(const u32 val) noexcept { set(Register::R15, val); }

        [[nodiscard]] u32 sp() const noexcept { return r13(); }
        void sp(const u32 val) noexcept { r13(val); }

        [[nodiscard]] u32 lr() const noexcept { return r14(); }
        void lr(const u32 val) noexcept { r14(val); }

        [[nodiscard]] u32 pc() const noexcept { return r15(); }
        void pc(const u32 val) noexcept { r15(val); }

        [[nodiscard]] u32 cpsr() const noexcept { return get(Register::CPSR); }
        void cpsr(const u32 val) noexcept { set(Register::CPSR, val); }

        [[nodiscard]] u32 spsr() const noexcept { return get(Register::SPSR); }
        void spsr(const u32 val) noexcept { set(Register::SPSR, val); }
    };

}