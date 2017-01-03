; GETDRV.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc

	.code

getdrv	PROC _CType PUBLIC
	mov	ah,19h
	int	21h
	mov	ah,0
	ret
getdrv	ENDP

	END
