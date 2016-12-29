include stdlib.inc
include crtl.inc

ifdef __W95__

PUBLIC	pGetForegroundWindow
extrn	user32_dll:BYTE

	.data
	pGetForegroundWindow dd dummy
	.code
Install:
	.if	GetModuleHandle( addr user32_dll )
		.if	GetProcAddress( eax, "GetForegroundWindow" )
			mov pGetForegroundWindow,eax
		.endif
	.endif
dummy:	xor	eax,eax
	ret

pragma_init Install,6

endif
	END
