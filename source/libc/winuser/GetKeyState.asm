include stdlib.inc
include crtl.inc
include winuser.inc

if (WINVER LT 0x0500)

	.data
	externdef	user32_dll:BYTE
	GetKeyState	GetKeyState_T dummy

	.code

dummy	proc WINAPI private
	xor eax,eax
	ret 4
dummy	endp

Install:
	.if GetModuleHandle( addr user32_dll )

		.if GetProcAddress( eax, "GetKeyState" )

			mov GetKeyState,eax
		.endif
	.endif
	ret

pragma_init Install,6

endif
	END
