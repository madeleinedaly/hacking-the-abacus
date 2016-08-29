;; invoke the write(2) system call
;; write(int fd, void* buf, size_t length)
;; eax/4 ebx/1   ecx/mesg   edx/15
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
