.section .text
.global _start

_start:
    B there
    BL here
    BLCC here

there:
    B _start

here:
    BAL there
