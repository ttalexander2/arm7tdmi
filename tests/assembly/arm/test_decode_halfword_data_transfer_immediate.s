.section .text
.global _start

_start:
    LDRH R1,[R2,#-14]!
    STRH R3, [R4, #2]
    LDRSB R8,[R2, #12]
    LDRNESH R11,[R0, #16]
