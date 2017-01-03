; GETYEAR.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

getyear PROC _CType PUBLIC USES cx
	mov	ah,2Ah
	int	21h
	mov	ax,cx
	ret
getyear ENDP

	END
