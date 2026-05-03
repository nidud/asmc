
;--- v2.19: emit a warning at least ( masm throws an error )

	.386
	.model small
	option casemap:none

	.code
x3:
x4:
start32:
	pushw offset x3
	pushw offset x4
	mov ax,4C00h
	int 21h

	END
