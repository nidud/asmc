; PUTEDXAL.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

putedxal PROC PUBLIC
	aam
	add	ax,3030h
	mov	es:[bx],ah
	inc	bx
	mov	es:[bx],al
	inc	bx
	ret
putedxal ENDP

	END
