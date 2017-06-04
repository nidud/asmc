include direct.inc
include errno.inc
include stdlib.inc
include winbase.inc

	.code

_chdir	PROC directory:LPSTR

local	abspath[_MAX_PATH]:BYTE

	.if	SetCurrentDirectory( directory )

		.if	GetCurrentDirectory( _MAX_PATH, addr abspath )

			mov	ecx,DWORD PTR abspath
			.if	ch == ':'

				mov	eax,003A003Dh
				mov	ah,cl
				.if	ah >= 'a' && ah <= 'z'
					sub	ah,'a' - 'A'
				.endif
				push	eax
				mov	ecx,esp
				lea	eax,abspath
				SetEnvironmentVariable( ecx, eax )
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
_chdir	ENDP

	END
