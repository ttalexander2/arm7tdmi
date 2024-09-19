.section .text
.thumb
.global _start

_start:
    CMP R0, #45
    BEQ other
    BNE other
    BCS other
    BCC other
    BMI other
    BPL other
    BVS other
    BVC other
    BHI other
    BLS other
    BGE other
    BLT other
    BGT other
    BLE other

other:
    BEQ _start
