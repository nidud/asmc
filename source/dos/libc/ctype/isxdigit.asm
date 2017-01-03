; ISXDIGIT.ASM--
; Copyright (C) 2015 Doszip Developers

include ctype.inc

	.code

isxdigit PROC PUBLIC USES ax
	call	getctype
	test	ah,_HEX
	ret
isxdigit ENDP

	END

