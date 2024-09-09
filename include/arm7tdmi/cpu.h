//
// Created by talexander on 9/6/2024.
//

#pragma once

#include "types.h"
#include "util.h"

namespace arm7tdmi {

    constexpr u32 CPSR_N = 31;
    constexpr u32 CPSR_Z = 30;
    constexpr u32 CPSR_C = 29;
    constexpr u32 CPSR_V = 28;

    class cpu {
    public:

        enum class cpu_mode : u8 {
            arm,
            thumb
        };

        enum class condition_code : u8
        {
            equal = 0,
            nequal = 1,
            unsigned_higher_or_same = 2,
            unsigned_lower = 3,
            negative = 4,
            positive_or_zero = 5,
            overflow = 6,
            no_overflow = 7,
            unsigned_higher = 8,
            unsigned_lower_or_same = 9,
            greater_or_equal = 10,
            less_than = 11,
            greater_than = 12,
            less_than_or_equal = 13,
            always = 14,
            never = 15
        };

        // Storage for registers
        struct
        {
            union { // Using a union here to have multiple aliases for accessing registers.
                u32 data[18] = {};

                struct {
                    u32 r0;
                    u32 r1;
                    u32 r2;
                    u32 r3;
                    u32 r4;
                    u32 r5;
                    u32 r6;
                    u32 r7;
                    u32 r8;
                    u32 r9;
                    u32 r10;
                    u32 r11;
                    u32 r12;

                    union {
                        u32 r13;
                        u32 sp;
                    };

                    union {
                        u32 r14;
                        u32 lp;
                    };

                    union {
                        u32 r15;
                        u32 pc;
                    };

                    struct {
                        u32 cpsr_register;

                        [[nodiscard]] bool n() const { return bit_check(cpsr_register, CPSR_N); }
                        u32 set_n(const bool val) { return cpsr_register = bit_set_to(cpsr_register, CPSR_N, val);}

                        [[nodiscard]] bool c() const { return bit_check(cpsr_register, CPSR_C); }
                        u32 set_c(const bool val) { return cpsr_register = bit_set_to(cpsr_register, CPSR_C, val);}

                        [[nodiscard]] bool v() const { return bit_check(cpsr_register, CPSR_V); }
                        u32 set_v(const bool val) { return cpsr_register = bit_set_to(cpsr_register, CPSR_V, val);}

                        [[nodiscard]] bool z() const { return bit_check(cpsr_register, CPSR_Z); }
                        u32 set_z(const bool val) { return cpsr_register = bit_set_to(cpsr_register, CPSR_Z, val);}

                        // ReSharper disable once CppNonExplicitConversionOperator
                        operator u32&() { return cpsr_register;} // NOLINT(*-explicit-constructor)

                        u32 operator=(const u32 &val) { return cpsr_register = val;} // NOLINT(*-unconventional-assign-operator)

                    } cpsr;

                    u32 spsr;
                };
            };

        } registers;





    private:
        cpu_mode mode = cpu_mode::arm;

    };

}
