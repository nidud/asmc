; MEMSET.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

memset	PROC _CType PUBLIC USES di string:PTR BYTE, char:size_t, count:size_t
	mov	cx,count
	les	di,string
	cld?
	mov	al,BYTE PTR char
	rep	stosb
	lodm	string
	ret
memset	ENDP

	END
