include stdlib.inc
include crtl.inc
include winuser.inc

if (_WIN32_WINNT LT 0x0500)

	extrn	user32_dll:BYTE

	.data
	GetForegroundWindow GetForegroundWindow_T dummy

	.code

Install:
	.if	GetModuleHandle( addr user32_dll )

		.if	GetProcAddress( eax, "GetForegroundWindow" )

			mov GetForegroundWindow,eax
		.endif
	.endif

dummy	proc _CType private
	xor	eax,eax
	ret
dummy	endp

pragma_init Install,6

endif
	END
