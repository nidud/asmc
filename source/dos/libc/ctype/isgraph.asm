; ISGRAPH.ASM--
; Copyright (C) 2015 Doszip Developers

include ctype.inc

isprint PROTO

	.code

isgraph PROC PUBLIC
	cmp	al,' '
	je	@F
	jmp	isprint
     @@:
	ret
isgraph ENDP

	END

