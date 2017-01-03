; ISPRINT.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc

	.code

isprint PROC PUBLIC
	cmp	al,20h
	jb	@F
	cmp	al,7Eh
	ja	@F
	test	al,al
	ret
     @@:
	cmp	al,al
	ret
isprint ENDP

	END

