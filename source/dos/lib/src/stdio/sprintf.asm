; SPRINTF.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

sprintf PROC _CDecl PUBLIC USES bx string:DWORD, format:DWORD, argptr:VARARG
local	o:S_FILE
	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,INT_MAX
	lodm	string
	stom	o.iob_bp
	stom	o.iob_base
	push	es
	invoke	_output,addr o,format,addr argptr
	les	bx,o.iob_bp
	mov	BYTE PTR es:[bx],0
	pop	es
	ret
sprintf ENDP

	END
