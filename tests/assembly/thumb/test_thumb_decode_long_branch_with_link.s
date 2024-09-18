.section .text
.thumb
.global _start

_start:
    BL faraway

next:
    BL _start

faraway:
    BL next
