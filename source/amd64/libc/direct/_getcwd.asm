include direct.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_getcwd PROC buffer:LPSTR, maxlen:SINT
	mov	r8d,edx
	mov	rdx,rcx
	_getdcwd( 0, rdx, r8d )
	ret
_getcwd ENDP

	END
