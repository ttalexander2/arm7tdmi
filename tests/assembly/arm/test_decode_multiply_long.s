.section .text
.global _start

_start:
    UMULL R1,R4,R2,R3
    UMLALS R1,R5,R2,R3
