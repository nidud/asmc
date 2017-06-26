; CURSORX.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

cursorx PROC _CType PUBLIC
	push	bx
	mov	bh,0
	mov	ah,3
	int	10h
	xor	ax,ax
	mov	al,dl
	mov	dl,dh
	mov	dh,0
	pop	bx
	ret
cursorx ENDP

	END
