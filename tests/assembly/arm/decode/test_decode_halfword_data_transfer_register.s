.section .text
.global _start

_start:
    LDRH R1,[R2,-R3]!
    STRH R3, [R4, R2]
    LDRSB R8,[R2],-R1
    LDRNESH R11,[R0, R1]
