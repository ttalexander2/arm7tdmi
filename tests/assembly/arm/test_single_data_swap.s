.section .text
.global _start

_start:
    SWP R0,R1,[R2]
    SWPB R2,R3,[R4]
    SWPEQ R0,R0,[R1]
