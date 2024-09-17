.section .text
.global _start

_start:
    ADDEQ R2,R4,R5
    TEQ R4,#3
    SUB R4,R5,R7,LSR R2
    MOV PC,R14
    MOVS PC,R14
