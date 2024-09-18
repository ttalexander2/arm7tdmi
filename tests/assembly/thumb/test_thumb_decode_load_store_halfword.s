.section .text
.thumb
.global _start

_start:
    STRH R6, [R1, #56]
    LDRH R4, [R7, #4]
