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

        union {
            u32 registers[18] = {};
            
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
                    u32 data;

                    [[nodiscard]] bool n() const { return bit_check(data, CPSR_N); }
                    u32 set_n(const bool val) { return data = bit_set_to(data, CPSR_N, val);}

                    [[nodiscard]] bool c() const { return bit_check(data, CPSR_C); }
                    u32 set_c(const bool val) { return data = bit_set_to(data, CPSR_C, val);}

                    [[nodiscard]] bool v() const { return bit_check(data, CPSR_V); }
                    u32 set_v(const bool val) { return data = bit_set_to(data, CPSR_V, val);}

                    [[nodiscard]] bool z() const { return bit_check(data, CPSR_Z); }
                    u32 set_z(const bool val) { return data = bit_set_to(data, CPSR_Z, val);}

                    // ReSharper disable once CppNonExplicitConversionOperator
                    operator u32&() { return data;} // NOLINT(*-explicit-constructor)

                    u32 operator=(const u32 &val) { return data = val;} // NOLINT(*-unconventional-assign-operator)

                } cpsr;

                u32 spsr;
            };
        };




    private:
        cpu_mode mode = cpu_mode::arm;

    };

}
