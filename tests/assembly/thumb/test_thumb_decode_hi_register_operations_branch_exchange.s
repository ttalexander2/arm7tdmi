.section .text
.thumb
.global _start

_start:
    ADD PC, R5
    CMP R4, R12
    MOV R15, R14
    MOV R11,R1
    BX R11
