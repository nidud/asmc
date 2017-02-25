include io.inc
include errno.inc
include winbase.inc

	.code

_osopenW PROC USES ebx,
	lpFileName:	LPWSTR,
	dwAccess:	SIZE_T,
	dwShareMode:	SIZE_T,
	lpSecurity:	PVOID,
	dwCreation:	SIZE_T,
	dwAttributes:	SIZE_T

	xor	eax,eax
	.while	_osfile[eax] & FH_OPEN

		inc	eax
		.if	eax == _nfile

			xor	eax,eax
			mov	oserrno,eax ; no OS error
			mov	errno,EBADF
			dec	eax
			jmp	toend
		.endif
	.endw
	mov	ebx,eax

	CreateFileW( lpFileName, dwAccess, dwShareMode, lpSecurity, dwCreation, dwAttributes, 0 )
	mov	edx,eax
	inc	eax
	jz	error
done:
	mov	eax,ebx
	mov	_osfhnd[eax*4],edx
	or	_osfile[eax],FH_OPEN
toend:
	ret
error:
	call	osmaperr
	jmp	toend
_osopenW ENDP

	END
