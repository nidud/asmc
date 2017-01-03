; OCPUTC.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc

	.code

ocputc	PROC _CType PUBLIC USES bx char:size_t
	mov	ax,char
	mov	bx,STDO.ios_i
	cmp	bx,STDO.ios_size
	je	oputc_flush
    oputc_ok:
	les	bx,STDO.ios_bp
	add	bx,STDO.ios_i
	inc	STDO.ios_i
	mov	es:[bx],al
	mov	ax,1
    oputc_eof:
	ret
    oputc_flush:
	push	cx
	push	dx
	push	ax
	call	oflush
	pop	ax
	pop	dx
	pop	cx
	jnz	oputc_ok
	xor	ax,ax
	jmp	oputc_eof
ocputc	ENDP

	END
