; ISDIGIT.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
include ctype.inc

	.code

isdigit PROC PUBLIC USES ax
	call getctype
	test ah,_DIGIT
	ret
isdigit ENDP

	END

