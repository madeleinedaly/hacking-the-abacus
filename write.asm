BITS 64
GLOBAL _start
SECTION .data
mesg:
        db "hello hackers", 0xa
SECTION .text
_start:
        mov     eax, 4
        mov     ebx, 1
        mov     ecx, mesg
        mov     edx, 15
        int     0x80
        mov     ebx, eax
        mov     eax, 1
        int     0x80
