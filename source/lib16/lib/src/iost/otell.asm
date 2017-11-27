; OTELL.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc

	.code

otell	PROC PUBLIC
	mov	ax,WORD PTR STDO.ios_total
	mov	dx,WORD PTR STDO.ios_total+2
	add	ax,STDO.ios_i
	adc	dx,0
	ret
otell	ENDP

	END
