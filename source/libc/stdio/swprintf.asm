include stdio.inc
include limits.inc

	.code

swprintf proc c uses ecx string:LPWSTR, format:LPWSTR, argptr:VARARG

  local o:_iobuf

	mov o._flag,_IOWRT or _IOSTRG
	mov o._cnt,INT_MAX
	mov eax,string
	mov o._ptr,eax
	mov o._base,eax

	_woutput(addr o, format, addr argptr)

	mov ecx,o._ptr
	mov WORD ptr [ecx],0
	ret

swprintf ENDP

	END
