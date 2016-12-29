include io.inc

	.code

_access PROC fname:LPSTR, amode:SIZE_T
	.if	getfattr( fname ) != -1
		.if	amode == 2 && eax & _A_RDONLY
			mov eax,-1
		.else
			xor eax,eax
		.endif
	.endif
	ret
_access ENDP

	END