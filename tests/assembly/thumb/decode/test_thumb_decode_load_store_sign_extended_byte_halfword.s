.section .text
.thumb
.global _start

_start:
    STRH R4, [R3, R0]
    LDSB R2, [R7, R1]
    LDSH R3, [R4, R2]
