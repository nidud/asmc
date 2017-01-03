; OREAD.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc

	.code

oread	PROC PUBLIC
	les	bx,STDI.ios_bp
	mov	dx,STDI.ios_i
	add	bx,dx
	mov	cx,STDI.ios_c
	sub	cx,dx
	cmp	cx,ax
	jb	oread_01
	mov	ax,cx
    oread_00:
	test	ax,ax
	ret
    oread_01:
	push	ax
	call	ofread
	pop	ax
	jz	oread_02
	mov	cx,STDI.ios_c
	sub	cx,STDI.ios_i
	cmp	cx,ax
	jae	oread
    oread_02:
	xor	ax,ax
	jmp	oread_00
oread	ENDP

	END
