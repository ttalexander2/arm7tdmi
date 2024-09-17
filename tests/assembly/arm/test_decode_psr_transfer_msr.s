.section .text
.global _start

_start:
    MSR CPSR_all,R2
    MSR CPSR_flg,R9
    MSR CPSR_flg,#0xA0000000
    MSR CPSR_flg,#0x50000000
    MSR SPSR_all,R4
    MSR SPSR_flg,R3
    MSR SPSR_flg,#0xC0000000
