.section .text
.global _start

_start:
    MRS R2, CPSR
    MRS R5, CPSR_all
    MRS R9, SPSR
    MRS R12,SPSR_all
