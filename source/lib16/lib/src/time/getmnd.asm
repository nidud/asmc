; GETMND.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

getmnd	PROC _CType PUBLIC USES cx
	mov	ah,2Ah
	int	21h
	mov	ah,0
	mov	al,dh
	ret
getmnd	ENDP

	END
