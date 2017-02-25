include stdio.inc
include limits.inc
IFDEF	_UNICODE
VSPRINTF equ <vswprintf>
OUTPUT	 equ <_woutput>
ELSE
VSPRINTF equ <vsprintf>
OUTPUT	 equ <_output>
ENDIF
	.code

VSPRINTF PROC USES ecx string:LPTSTR, format:LPTSTR, vargs:PVOID
local	o:_iobuf
	mov	o._flag,_IOWRT or _IOSTRG
	mov	o._cnt,INT_MAX
	mov	eax,string
	mov	o._ptr,eax
	mov	o._base,eax
	OUTPUT( addr o, format, vargs )
	mov	ecx,o._ptr
	mov	TCHAR PTR [ecx],0
	ret
VSPRINTF ENDP

	END
