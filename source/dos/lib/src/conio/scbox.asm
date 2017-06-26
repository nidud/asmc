; SCBOX.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

	.code

scbox	PROC _CType PUBLIC x, y, col, row, btype, color:size_t
	HideMouseCursor
	mov	al,BYTE PTR col
	mov	ah,BYTE PTR row
	push	ax
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	push	ax
	push	_scrseg
	push	0
	push	80
	mov	ah,BYTE PTR color
	mov	al,BYTE PTR btype
	push	ax
	call	rcframe
	ShowMouseCursor
	ret
scbox	ENDP

	END
