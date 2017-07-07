include io.inc

	.code

	option win64:rsp

_access PROC fname:LPSTR, amode:UINT
	.if getfattr(rcx) != -1
	    .if amode == 2 && eax & _A_RDONLY
		mov eax,-1
	    .else
		xor eax,eax
	    .endif
	.endif
	ret
_access ENDP

	END