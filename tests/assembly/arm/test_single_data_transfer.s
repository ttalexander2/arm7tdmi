.section .text
.global _start

_start:
    STR R1,[R2,R4]!
    STR R1,[R2],R4
    LDR R1,[R2,#16]
    LDR R1,[R2,R3,LSL#2]
    LDREQB R1, [R6, $5]
