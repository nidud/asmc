; GETCTYPE.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
include ctype.inc

	.code

getctype PROC PUBLIC USES bx
	sub	bx,bx
	mov	bl,al
	mov	ah,ss:[bx+__ctype+1]
	test	al,al
	ret
getctype ENDP

	END

