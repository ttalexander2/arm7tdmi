.section .text
.thumb
.global _start

_start:
    STR R3, [R2,R6]
    LDRB R2, [R0,R7]
