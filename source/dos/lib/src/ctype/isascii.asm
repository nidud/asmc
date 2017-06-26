; ISASCII.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc

	.code

isascii PROC PUBLIC
	cmp	al,128
	jnb	isnotascii
	push	ax
	or	al,1
	pop	ax
	ret
    isnotascii:
	cmp	al,al
	ret
isascii ENDP

	END

