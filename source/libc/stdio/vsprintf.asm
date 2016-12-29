include stdio.inc
include limits.inc

	.code

vsprintf PROC USES ecx string:LPSTR, format:LPSTR, vargs:PVOID
local	o:S_FILE

	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,INT_MAX
	mov	eax,string
	mov	o.iob_ptr,eax
	mov	o.iob_base,eax
	_output( addr o, format, vargs )
	mov	ecx,o.iob_ptr
	mov	BYTE PTR [ecx],0

	ret
vsprintf ENDP

	END
