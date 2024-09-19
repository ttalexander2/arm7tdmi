.section .text
.thumb
.global _start

_start:
    AND R2, R3
    EOR R6, R3
    LSL R7, R2
    LSR R3, R6
    ASR R5, R6
    ADC R7, R2
    SBC R2, R3
    ROR R2, R5
    TST R1, R7
    NEG R2, R5
    CMP R1, R3
    CMN R2, R5
    ORR R5, R6
    MUL R3, R1
    BIC R3, R2
    MVN R2, R3
