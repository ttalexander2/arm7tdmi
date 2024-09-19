.section .text
.thumb
.global _start

_start:
    PUSH {R0-R4,LR}
    POP {R2,R6,PC}
