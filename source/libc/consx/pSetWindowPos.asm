include stdlib.inc
include crtl.inc

ifdef __W95__

PUBLIC	pSetWindowPos
extrn	user32_dll:BYTE

	.data
	pSetWindowPos dd dummy
	.code
dummy:
	xor	eax,eax
	ret	28
Install:
	.if GetModuleHandle( addr user32_dll )

		.if GetProcAddress( eax, "SetWindowPos" )

			mov pSetWindowPos,eax
		.endif
	.endif
	ret

pragma_init Install,6

endif

	END
