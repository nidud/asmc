; RCADDRC.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

rcaddrc PROC _CType PUBLIC USES bx result:DWORD, r1:DWORD, r2:DWORD
	lodm	r2
	add	ax,WORD PTR r1
	les	bx,result
	stom	es:[bx]
	ret
rcaddrc ENDP

	END