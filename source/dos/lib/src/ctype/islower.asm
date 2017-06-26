; ISLOWER.ASM--
; Copyright (C) 2015 Doszip Developers

include ctype.inc

	.code

islower PROC PUBLIC USES ax
	call	getctype
	test	ah,_LOWER
	ret
islower ENDP

	END

