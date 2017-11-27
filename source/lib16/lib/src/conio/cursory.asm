; CURSORY.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

cursory PROC _CType PUBLIC
	push	bx
	mov	bh,0
	mov	ah,3
	int	10h
	xor	ax,ax
	mov	al,dh
	pop	bx
	ret
cursory ENDP

	END
