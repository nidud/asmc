; GOTOXY.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

gotoxy	PROC _CType PUBLIC x:size_t, y:size_t
	push	bx
	mov	dh,BYTE PTR y
	mov	dl,BYTE PTR x
	mov	bh,0
	mov	ah,2
	int	10h
	pop	bx
	ret
gotoxy	ENDP

	END
