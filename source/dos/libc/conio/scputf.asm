; SCPUTF.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include stdio.inc

	.code

scputf	PROC _CDecl PUBLIC USES dx cx x, y, a, l:size_t, f:DWORD, p:VARARG
	invoke ftobufin,f,addr p
	invoke scputs,x,y,a,l,addr _bufin
	ret
scputf	ENDP

	END
