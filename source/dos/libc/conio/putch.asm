; PUTCH.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include io.inc

	.code

putch	PROC _CType PUBLIC char:size_t
	invoke	write,2,addr char,1
	ret
putch	ENDP

	END
