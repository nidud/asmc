; FTOBUFIN.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

ftobufin PROC _CDecl PUBLIC USES bx format:DWORD, argptr:VARARG
local	o:S_FILE
	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,_INTIOBUF
	mov	_bufin,0
	mov	ax,offset _bufin
	mov	dx,ds
	stom	o.iob_bp
	stom	o.iob_base
	invoke	_output,addr o,format,DWORD PTR argptr
	mov	bx,WORD PTR o.iob_bp
	mov	BYTE PTR [bx],0
	mov	dx,bx
	ret
ftobufin ENDP

	END
