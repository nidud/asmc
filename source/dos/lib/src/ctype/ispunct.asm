; ISPUNCT.ASM--
; Copyright (C) 2015 Doszip Developers

include ctype.inc

	.code

ispunct PROC PUBLIC USES ax
	call	getctype
	test	ah,_PUNCT
	ret
ispunct ENDP

	END

