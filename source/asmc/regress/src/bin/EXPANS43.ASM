
;--- v2.15: fixed
;--- previously: error 'missing operator in expression'

	.386
	.model flat

C1 equ 1

RM macro x
	exitm <x+C1>
endm

CMASK equ RM(0) or RM(1)

	.code
	mov eax, CMASK

	END

