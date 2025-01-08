.section .text
.global _start

_start:
    LDMFD SP!,{R0,R1,R2}        @ Unstack 3 registers.
    STMIA R0,{R0-R15}           @ Save all registers.
    LDMFD SP!,{R15}             @ R15 <- (SP),CPSR unchanged.

    LDMFD SP!,{R15}^            @ R15 <- (SP), CPSR <- SPSR_mode
                                @ (allowed only in privileged modes).

    STMFD R13,{R0-R14}^         @ Save user mode regs on stack
                                @ (allowed only in privileged modes).

    STMED SP!,{R0-R3,R14}       @ Save R0 to R3 to use as workspace
                                @ and R14 for returning.
    BL somewhere                @ This nested call will overwrite R14
    LDMED SP!,{R0-R3,R15}       @ restore workspace and return.

somewhere:
    MOV PC,R14
