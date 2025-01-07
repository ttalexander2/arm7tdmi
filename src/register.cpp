//
// Created by talexander on 1/7/2025.
//

#include <arm7tdmi/register.h>

namespace arm7tdmi {

    cpu_register& cpu_register_subset::operator[](const size_t index) const {
        switch (index) {
            case 0:  return r0;
            case 1:  return r1;
            case 2:  return r2;
            case 3:  return r3;
            case 4:  return r4;
            case 5:  return r5;
            case 6:  return r6;
            case 7:  return r7;
            case 8:  return r8;
            case 9:  return r9;
            case 10: return r10;
            case 11: return r11;
            case 12: return r12;
            case 13: return r13;
            case 14: return r14;
            case 15: return r15;
            case 16: return cpsr;
            case 17: return spsr;
            default: return r0;
        }
    }

    // this is gross, but it makes the api look nice haha
    cpu_register_set::cpu_register_set() :
                                           user_subset{
                                               r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13,
                                               r14, r15, cpsr, spsr_fiq
                                           },
                                           fiq_subset{
                                               r0, r1, r2, r3, r4, r5, r6, r7, r8_fiq, r9_fiq, r10_fiq,
                                               r11_fiq, r12_fiq, r13_fiq, r14_fiq, r15, cpsr, spsr_fiq
                                           },
                                           irq_subset{
                                               r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
                                               r13_irq, r14_irq, r15, cpsr, spsr_irq
                                           },
                                           supervisor_subset{
                                               r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
                                               r13_svc, r14_svc, r15, cpsr, spsr_svc
                                           },
                                           abort_subset{
                                               r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
                                               r13_abt, r14_abt, r15, cpsr, spsr_abt
                                           },
                                           undefined_subset{
                                               r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12,
                                               r13_und, r14_und, r15, cpsr, spsr_und
                                           },
                                           system_subset{
                                               r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13,
                                               r14, r15, cpsr, spsr_fiq
                                           }
    {
    }

    const cpu_register_subset& cpu_register_set::subset(const cpu_mode mode) const {
        switch (mode) {
            case cpu_mode::fiq:
                return fiq_subset;
            case cpu_mode::irq:
                return irq_subset;
            case cpu_mode::supervisor:
                return supervisor_subset;
            case cpu_mode::abort:
                return abort_subset;
            case cpu_mode::undefined:
                return undefined_subset;
            case cpu_mode::system:
            case cpu_mode::user:
            default:
                return user_subset;
        }
    }
}
