; OCLOSE.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc

	.code

oclose	PROC _CType PUBLIC io:DWORD
	mov	bx,WORD PTR io
	push	[bx].S_IOST.ios_file
	mov	[bx].S_IOST.ios_file,-1
	invoke	ofreest,io
	call	close
	ret
oclose	ENDP

	END
