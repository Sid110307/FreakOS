MBFLAGS  equ  (1 << 0) | (1 << 1)
MAGIC    equ  0x1BADB002

section .multiboot
    align 4
    dd MAGIC
    dd MBFLAGS
    dd -(MAGIC + MBFLAGS)
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 0
    dd 800
    dd 600
    dd 32

section .bss
    align 16
    stackBottom: resb 16384
    stackTop:

section .text
	global _start

_start:
	mov esp, stackTop
	extern main
	call main

	cli

.hang:
	hlt
	jmp .hang
.end:
