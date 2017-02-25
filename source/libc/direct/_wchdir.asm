include direct.inc
include errno.inc
include winbase.inc

	.code

_wchdir PROC directory:LPWSTR

local	abspath[_MAX_PATH]:WORD

	.if	SetCurrentDirectoryW( directory )

		.if	GetCurrentDirectoryW( _MAX_PATH, addr abspath )

			mov	cl,byte ptr abspath
			mov	ch,byte ptr abspath[2]
			.if	ch == ':'
				push	0x0000003A
				movzx	eax,cl
				.if	al >= 'a' && al <= 'z'
					sub	al,'a' - 'A'
				.endif
				shl	eax,16
				mov	al,0x3D
				push	eax
				mov	ecx,esp
				lea	eax,abspath
				SetEnvironmentVariableW( ecx, eax )
				pop	ecx
				pop	ecx
				test	eax,eax
				jz	error
			.endif
			xor	eax,eax
			jmp	toend
		.endif
	.endif
error:
	call	osmaperr
toend:
	ret
_wchdir ENDP

	END
