; SCPUTC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

.code

scputc	PROC _CType PUBLIC x:size_t, y:size_t, l:size_t, char:size_t
	mov	al,BYTE PTR char
	mov	ah,0
	invoke	scputw,x,y,l,ax
	ret
scputc	ENDP

	END
