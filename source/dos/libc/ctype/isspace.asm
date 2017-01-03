; ISSPACE.ASM--
; Copyright (C) 2015 Doszip Developers

include ctype.inc

	.code

isspace PROC PUBLIC USES ax
	call	getctype
	test	ah,_SPACE
	ret
isspace ENDP

	END

