; GETHOUR.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

gethour PROC _CType PUBLIC
	mov	ah,2Ch
	int	21h
	mov	al,ch
	mov	ah,0
	ret
gethour ENDP

	END
