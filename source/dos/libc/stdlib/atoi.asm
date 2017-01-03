; ATOI.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc

	.code

atoi	PROC _CType PUBLIC string:DWORD
	invoke	atol,string
	ret
atoi	ENDP

	END
