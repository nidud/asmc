; PRINTF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

printf	PROC _CDecl PUBLIC format:DWORD, argptr:VARARG
	invoke	_stbuf,addr stdout
	push	ax
	invoke	_output,addr stdout,format,addr argptr
	pop	dx
	push	ax
	invoke	_ftbuf,dx,addr stdout
	pop	ax
	ret
printf	ENDP

	END
