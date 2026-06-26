
;--- xlat errors
;--- jwasm: invalid instruction operands
;---  masm: invalid operand size for instruction

	.286
	.model small
	option casemap:none

	.data

m16	dw 0
m32	dd 0

	.code

	xlatb word ptr cs:[bx]
	xlatb m32

	end
