MBALIGN  equ  1 << 0
MEMINFO  equ  1 << 1
MBFLAGS  equ  MBALIGN | MEMINFO
MAGIC    equ  0x1BADB002
CHECKSUM equ -(MAGIC + MBFLAGS)

section .multiboot
align 4
dd MAGIC
dd MBFLAGS
dd CHECKSUM

section .bss
align 16

stackBottom:
	resb 16384

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
