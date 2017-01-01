include stdio.inc
include limits.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

vsprintf PROC USES rcx,
	string: LPSTR,
	format: LPSTR,
	vargs:	PVOID
local	o:	S_FILE

	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,INT_MAX
	mov	o.iob_ptr,rcx
	mov	o.iob_base,rcx
	_output( addr o, rdx, r8 )
	mov	rcx,o.iob_ptr
	mov	BYTE PTR [rcx],0

	ret
vsprintf ENDP

	END
