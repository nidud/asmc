; GETXYW.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

	.code

getxyw	PROC _CType PUBLIC USES bx x:size_t, y:size_t
	push	dx
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	call	__getxypm
	mov	es,dx
	mov	bx,ax
	mov	ax,es:[bx]
	ShowMouseCursor
	pop	dx
	ret
getxyw	ENDP

	END
