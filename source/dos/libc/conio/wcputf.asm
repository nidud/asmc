; WCPUTF.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include stdio.inc

	.code

wcputf	PROC _CDecl PUBLIC b:DWORD, l:size_t, max:size_t, format:DWORD, argptr:VARARG
	invoke ftobufin,format,addr argptr
	invoke wcputs,b,l,max,addr _bufin
	ret
wcputf	ENDP

	END
