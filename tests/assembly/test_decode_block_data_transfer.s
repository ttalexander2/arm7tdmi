.section .text
.global _start

_start:
    LDMFD SP!,{R0,R1,R2}
    LDMFD SP!,{R15}
    LDMED SP!,{R0-R3,R15}
    STMFD R13,{R0-R14}^
    STMED SP!,{R0-R3,R14}
