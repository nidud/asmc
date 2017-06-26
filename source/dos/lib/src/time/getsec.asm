; GETSEC.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

getsec	PROC _CType PUBLIC
	mov	ah,2Ch
	int	21h
	mov	al,dh
	mov	ah,0
	ret
getsec	ENDP

	END
