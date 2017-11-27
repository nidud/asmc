; GETMIN.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

getmin	PROC _CType
	mov	ah,2Ch
	int	21h
	mov	al,cl
	mov	ah,0
	ret
getmin	ENDP

	END
