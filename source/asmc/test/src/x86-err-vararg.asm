
;--- a vararg argument is used inside a "vararg" proc to call another "vararg proc.
;--- was accepted until v2.18

	.386
	.model flat, stdcall
	option casemap:none

	.code

pr1 proc c a1:dword, a2:vararg
	ret
pr1 endp

pr2 proc c a1:dword, a2:vararg

	nop
	invoke pr1, a1, a2
	ret
pr2 endp


start:
	invoke pr2, 1, 2, 3
	ret

	end start
