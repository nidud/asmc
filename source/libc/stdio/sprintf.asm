include stdio.inc
include limits.inc

	.code

sprintf PROC C USES ecx string:LPSTR, format:LPSTR, argptr:VARARG

local	o:S_FILE

	mov	o.iob_flag,_IOWRT or _IOSTRG
	mov	o.iob_cnt,INT_MAX
	mov	eax,string
	mov	o.iob_ptr,eax
	mov	o.iob_base,eax

	_output( addr o, format, addr argptr )

	mov	ecx,o.iob_ptr
	mov	byte ptr [ecx],0
	ret

sprintf ENDP

	END
