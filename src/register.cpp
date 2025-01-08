//
// Created by talexander on 1/7/2025.
//

#include <arm7tdmi/register.h>
#include <cassert>


namespace arm7tdmi {

    size_t cpu_registers::register_enum_to_index(const Register reg) const {
        const auto mode = cpsr_get_mode();

        switch (reg) {
            case Register::R0: return REG_R0;
            case Register::R1: return REG_R1;
            case Register::R2: return REG_R2;
            case Register::R3: return REG_R3;
            case Register::R4: return REG_R4;
            case Register::R5: return REG_R5;
            case Register::R6: return REG_R6;
            case Register::R7: return REG_R7;
            case Register::R8: return (mode == cpu_mode::fiq) ? REG_R8_FIQ : REG_R8;
            case Register::R9: return (mode == cpu_mode::fiq) ? REG_R9_FIQ : REG_R9;
            case Register::R10: return (mode == cpu_mode::fiq) ? REG_R10_FIQ : REG_R10;
            case Register::R11: return (mode == cpu_mode::fiq) ? REG_R11_FIQ : REG_R11;
            case Register::R12: return (mode == cpu_mode::fiq) ? REG_R12_FIQ : REG_R12;
            case Register::R13: {
                switch (mode) {
                    case cpu_mode::fiq: return REG_R13_FIQ;
                    case cpu_mode::supervisor: return REG_R13_SVC;
                    case cpu_mode::abort: return REG_R13_ABT;
                    case cpu_mode::irq: return REG_R13_IRQ;
                    case cpu_mode::undefined: return REG_R13_UNDEF;
                    case cpu_mode::system:
                    case cpu_mode::user:
                    default:
                        return REG_R13;
                }
            }
            case Register::R14: {
                switch (mode) {
                    case cpu_mode::fiq: return REG_R14_FIQ;
                    case cpu_mode::supervisor: return REG_R14_SVC;
                    case cpu_mode::abort: return REG_R14_ABT;
                    case cpu_mode::irq: return REG_R14_IRQ;
                    case cpu_mode::undefined: return REG_R14_UNDEF;
                    case cpu_mode::system:
                    case cpu_mode::user:
                    default:
                        return REG_R14;
                }
            }
            case Register::R15: return REG_R15;
            case Register::CPSR: return REG_CPSR;
            case Register::SPSR: {
                switch (mode) {
                    case cpu_mode::fiq: return REG_SPSR_FIQ;
                    case cpu_mode::supervisor: return REG_SPSR_SVC;
                    case cpu_mode::abort: return REG_SPSR_ABT;
                    case cpu_mode::irq: return REG_SPSR_IRQ;
                    case cpu_mode::undefined: return REG_SPSR_UNDEF;
                    default:
                        assert(false);
                        return REG_R0;
                }
            }
            default:
                assert(false);
                return REG_R0;
        }
    }

    Register cpu_registers::register_index_to_enum(const size_t index) {
        switch (index) {
            case REG_R0: return Register::R0;
            case REG_R1: return Register::R1;
            case REG_R2: return Register::R2;
            case REG_R3: return Register::R3;
            case REG_R4: return Register::R4;
            case REG_R5: return Register::R5;
            case REG_R6: return Register::R6;
            case REG_R7: return Register::R7;
            case REG_R8: return Register::R8;
            case REG_R9: return Register::R9;
            case REG_R10: return Register::R10;
            case REG_R11: return Register::R11;
            case REG_R12: return Register::R12;
            case REG_R13:
            case REG_R13_FIQ:
            case REG_R13_SVC:
            case REG_R13_ABT:
            case REG_R13_IRQ:
            case REG_R13_UNDEF: return Register::R13;
            case REG_R14:
            case REG_R14_FIQ:
            case REG_R14_SVC:
            case REG_R14_ABT:
            case REG_R14_IRQ:
            case REG_R14_UNDEF: return Register::R14;
            case REG_R15: return Register::R15;
            case REG_CPSR: return Register::CPSR;
            case REG_SPSR_FIQ:
            case REG_SPSR_SVC:
            case REG_SPSR_ABT:
            case REG_SPSR_IRQ:
            case REG_SPSR_UNDEF: return Register::SPSR;
            default:
                assert(false);
                return Register::R0;
        }
    }

    bool cpu_registers::cpsr_get_n() const {
        return util::bit_check(get(Register::CPSR), CPSR_N);
    }

    void cpu_registers::cpsr_set_n(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_N, value));
    }

    bool cpu_registers::cpsr_get_z() const {
        return util::bit_check(get(Register::CPSR), CPSR_Z);
    }

    void cpu_registers::cpsr_set_z(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_Z, value));
    }

    bool cpu_registers::cpsr_get_c() const {
        return util::bit_check(get(Register::CPSR), CPSR_C);
    }

    void cpu_registers::cpsr_set_c(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_C, value));
    }

    bool cpu_registers::cpsr_get_v() const {
        return util::bit_check(get(Register::CPSR), CPSR_V);
    }

    void cpu_registers::cpsr_set_v(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_V, value));
    }

    bool cpu_registers::cpsr_get_q() const {
        return util::bit_check(get(Register::CPSR), CPSR_Q);
    }

    void cpu_registers::cpsr_set_q(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_Q, value));
    }

    bool cpu_registers::cpsr_get_i() const {
        return util::bit_check(get(Register::CPSR), CPSR_I);
    }

    void cpu_registers::cpsr_set_i(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_I, value));
    }

    bool cpu_registers::cpsr_get_f() const {
        return util::bit_check(get(Register::CPSR), CPSR_F);
    }

    void cpu_registers::cpsr_set_f(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_F, value));
    }

    bool cpu_registers::cpsr_get_t() const {
        return util::bit_check(get(Register::CPSR), CPSR_T);
    }

    void cpu_registers::cpsr_set_t(const bool value) {
        set(Register::CPSR, util::bit_set_to(get(Register::CPSR), CPSR_T, value));
    }

    u32 cpu_registers::cpsr_get_m() const {
        return data[REG_CPSR] & CPSR_M;
    }

    void cpu_registers::cpsr_set_m(const u32 m) {
        set(Register::CPSR, (get(Register::CPSR) & ~CPSR_M) | (m & CPSR_M));
    }

    cpu_mode cpu_registers::cpsr_get_mode() const {
        return static_cast<cpu_mode>(cpsr_get_m());
    }

    void cpu_registers::cpsr_set_mode(cpu_mode mode) {
        cpsr_set_m(static_cast<u32>(mode));
    }
}
