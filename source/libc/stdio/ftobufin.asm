include stdio.inc

	.code

ftobufin PROC C,
	format: LPSTR,
	argptr: VARARG
local	o:	S_FILE
	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,_INTIOBUF
	mov	_bufin,0
	mov	eax,offset _bufin
	mov	o.iob_ptr,eax
	mov	o.iob_base,eax
	_output( addr o, format, dword ptr argptr )
	mov	edx,o.iob_ptr
	mov	byte ptr [edx],0
	mov	edx,offset _bufin
	ret
ftobufin ENDP

	END
