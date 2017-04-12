include io.inc
include errno.inc
include conio.inc

	.code

_osopenW PROC USES rsi rdi rbx,
	lpFileName:	LPWSTR,
	dwAccess:	DWORD,
	dwShareMode:	DWORD,
	lpSecurity:	PVOID,
	dwCreation:	DWORD,
	dwAttributes:	DWORD
local	NameW[2048]:SBYTE

	xor	eax,eax
	lea	rsi,_osfile
	.while	BYTE PTR [rsi+rax] & FH_OPEN
		inc	eax
		.if	eax == _nfile
			xor	eax,eax
			mov	oserrno,eax ; no OS error
			mov	errno,EBADF
			dec	rax
			jmp	toend
		.endif
	.endw
	mov	rbx,rax
	CreateFileW( lpFileName, dwAccess, dwShareMode, lpSecurity,
		dwCreation, dwAttributes, 0 )
	mov	rdx,rax
	inc	rax
	jz	error
done:
	mov	rax,rbx
	lea	rsi,_osfile
	or	BYTE PTR [rsi+rax],FH_OPEN
	lea	rsi,_osfhnd
	mov	[rsi+rax*8],rdx
toend:
	ret
error:
	call	osmaperr
	jmp	toend
_osopenW ENDP

	END
