.section .text
.global _start

_start:
    ADR R0, Into_THUMB + 1
    BX R0
    ADR R1, Into_ARM
    BX R1

.thumb
Into_THUMB:
    ADD R0, R1, R2

.arm
Into_ARM:
    BX R0
