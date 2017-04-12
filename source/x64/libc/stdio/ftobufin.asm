include stdio.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

ftobufin PROC format:LPSTR, argptr:VARARG
local	o:	_iobuf
	mov	o._flag,_IOWRT or _IOSTRG
	mov	o._cnt,_INTIOBUF
	mov	_bufin,0
	lea	rax,_bufin
	mov	o._ptr,rax
	mov	o._base,rax
	_output( addr o, format, qword ptr argptr )
	mov	rdx,o._ptr
	mov	byte ptr [rdx],0
	lea	rdx,_bufin
	ret
ftobufin ENDP

	END
