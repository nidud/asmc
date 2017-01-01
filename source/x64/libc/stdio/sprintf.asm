include stdio.inc
include limits.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

sprintf PROC USES rcx,
	string: LPSTR,
	format: LPSTR,
	argptr: VARARG
local	o:	S_FILE
	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,INT_MAX
	mov	o.iob_ptr,rcx
	mov	o.iob_base,rcx
	_output( addr o, format, addr argptr )
	mov	rcx,o.iob_ptr
	mov	byte ptr [rcx],0
	ret
sprintf ENDP

	END
