; STRLEN.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

strlen	PROC _CType PUBLIC USES di string:PTR BYTE
	cld?
	mov	al,0
	les	di,string
	mov	cx,-1
	repne	scasb
	mov	ax,cx
	not	ax
	dec	ax
	ret
strlen	ENDP

	END
