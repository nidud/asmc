; _PRINT.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc

	.code

_print	PROC _CDecl PUBLIC format:DWORD, argptr:VARARG
	invoke ftobufin,format,addr argptr
	invoke write,1,addr _bufin,ax
	ret
_print	ENDP

	END
