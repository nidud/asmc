; MEMZERO.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

memzero PROC _CType PUBLIC USES di s1:PTR BYTE, count:size_t
	mov	cx,count
	les	di,s1
	cld?
	sub	ax,ax
	rep	stosb
	ret
memzero ENDP

	END
