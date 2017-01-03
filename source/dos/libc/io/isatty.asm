; ISATTY.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc

	.code

isatty	PROC _CType PUBLIC handle:size_t
	push	bx
	mov	bx,handle
	mov	al,_osfile[bx]
	and	ax,FH_DEVICE
	pop	bx
	ret
isatty	ENDP

	END
