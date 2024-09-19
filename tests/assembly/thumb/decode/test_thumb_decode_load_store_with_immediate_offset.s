.section .text
.thumb
.global _start

_start:
    LDR R2, [R5,#116]
    STRB R1, [R0,#13]
