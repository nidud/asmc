
;--- 64-bit forward reference
;--- didn't work before v2.05 because the assembler
;--- assumed a 8-byte constant, which isn't an acceptable
;--- operand for CMP.

ifndef __ASMC64__
    .x64
    .model flat
endif

	.code

	cmp rax, [m64]
;	cmp rcx, E1

m64	dq 0

;E1	equ 0

	end
