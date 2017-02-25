include io.inc
include winbase.inc

	.code

osopenW PROC file:LPWSTR, attrib, mode, action

	xor	eax,eax
	mov	ecx,mode
	.if	ecx == M_RDONLY

		mov eax,FILE_SHARE_READ
	.endif

	_osopenW( file, ecx, eax, 0, action, attrib )
	ret

osopenW ENDP

	END
