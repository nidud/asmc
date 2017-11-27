; FPRINTF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

fprintf PROC _CDecl PUBLIC file:DWORD, format:DWORD, argptr:VARARG
	invoke	_stbuf,file
	push	ax
	invoke	_output,file,format,addr argptr
	pop	dx
	push	ax
	invoke	_ftbuf,dx,file
	pop	ax
	ret
fprintf ENDP

	END
