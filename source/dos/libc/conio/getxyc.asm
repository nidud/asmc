; GETXYC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include io.inc

	.code

getxyc	PROC _CType PUBLIC x:size_t, y:size_t
	invoke	getxyw,x,y
	mov	ah,0
	ret
getxyc	ENDP

	END
