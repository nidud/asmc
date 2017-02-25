include stdio.inc
include limits.inc
IFDEF	_UNICODE
SPRINTF equ <swprintf>
OUTPUT	equ <_woutput>
ELSE
SPRINTF equ <sprintf>
OUTPUT	equ <_output>
ENDIF
	.code

SPRINTF PROC C USES ecx string:LPTSTR, format:LPTSTR, argptr:VARARG

local	o:_iobuf

	mov	o._flag,_IOWRT or _IOSTRG
	mov	o._cnt,INT_MAX
	mov	eax,string
	mov	o._ptr,eax
	mov	o._base,eax

	OUTPUT( addr o, format, addr argptr )

	mov	ecx,o._ptr
	mov	TCHAR ptr [ecx],0
	ret

SPRINTF ENDP

	END
