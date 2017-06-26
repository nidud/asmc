; ISALPHA.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
include ctype.inc

	.code

isalpha PROC PUBLIC USES ax
	call getctype
	test ah,_UPPER or _LOWER
	ret
isalpha ENDP

	END

