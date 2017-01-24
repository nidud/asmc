include stdlib.inc
include crtl.inc

ifdef __W95__

PUBLIC	pGetKeyState

	.data

externdef	user32_dll:BYTE
pGetKeyState	dd dummy
cp_GetKeyState	db "GetKeyState",0

	.code

dummy:
	xor	eax,eax
	ret 4

Install:
	.if	GetModuleHandle( addr user32_dll )
		.if	GetProcAddress( eax, addr cp_GetKeyState )
			mov pGetKeyState,eax
		.endif
	.endif
	ret

pragma_init Install,6

endif
	END
