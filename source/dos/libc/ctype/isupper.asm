; ISUPPER.ASM--
; Copyright (C) 2015 Doszip Developers

include ctype.inc

	.code

isupper PROC PUBLIC USES ax
	call	getctype
	test	ah,_UPPER
	ret
isupper ENDP

	END

