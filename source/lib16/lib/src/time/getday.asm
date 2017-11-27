; GETDAY.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

getday	PROC _CType PUBLIC USES cx
	mov	ah,2Ah
	int	21h
	mov	ah,0
	mov	al,dl
	ret
getday	ENDP

	END
