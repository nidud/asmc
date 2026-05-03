
;--- v2.19: pe format and org in first section

	.386
	.model flat

DStr macro text:vararg
local sym
	.code _TEXT$2
sym db text,'$'
	.code
	exitm <offset sym>
endm

	.code

	org 100h

_start:
	mov edx, DStr("hello",13,10)
	mov ah, 9
	int 21h
	mov ax, 4c00h
	int 21h

	end _start
