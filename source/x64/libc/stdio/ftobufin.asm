include stdio.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

ftobufin PROC format:LPSTR, argptr:VARARG
local	o:	S_FILE
	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,_INTIOBUF
	mov	_bufin,0
	lea	rax,_bufin
	mov	o.iob_ptr,rax
	mov	o.iob_base,rax
	_output( addr o, format, qword ptr argptr )
	mov	rdx,o.iob_ptr
	mov	byte ptr [rdx],0
	lea	rdx,_bufin
	ret
ftobufin ENDP

	END
