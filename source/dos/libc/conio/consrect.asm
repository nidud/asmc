; CONSRECT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

consrect PROC _CType PUBLIC
	mov	dl,_scrcol
	mov	dh,_scrrow
	sub	ax,ax
	ret
consrect ENDP

	END
