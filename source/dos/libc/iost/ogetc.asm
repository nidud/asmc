; OGETC.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc

	.code

ogetc	PROC PUBLIC
	mov	ax,STDI.ios_i
	cmp	ax,STDI.ios_c
	je	ogetc_read
    ogetc_do:
	inc	STDI.ios_i
	les	bx,STDI
	add	bx,ax		; es:0 == zero flag set
	inc	ax
	mov	ah,0
	mov	al,es:[bx]
    ogetc_end:
	ret
    ogetc_read:
	push	cx
	push	dx
	call	ofread
	pop	dx
	pop	cx
	mov	ax,STDI.ios_i
	jnz	ogetc_do
	mov	ax,-1
	jmp	ogetc_end
ogetc	ENDP

	END
