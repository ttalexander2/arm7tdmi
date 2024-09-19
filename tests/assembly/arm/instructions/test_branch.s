.section .text
.global _start

_start:
    B there
    BL there
    BLCC there
    BEQ there
    BL there

there:
    MOV PC,R14
