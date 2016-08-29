BITS 64
GLOBAL _start
SECTION .text
_start:
        mov     eax, 1
        mov     ebx, 0x21
        int     0x80
