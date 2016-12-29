include consx.inc
include stdlib.inc
include crtl.inc

ifdef __W95__

PUBLIC	pGetConsoleWindow
extrn	kernel32_dll:BYTE

	.data
	pGetConsoleWindow dd dummy
	.code
Install:
	.if GetModuleHandle( addr kernel32_dll )
		.if GetProcAddress( eax, "GetConsoleWindow" )
			mov pGetConsoleWindow,eax
		.else
			and console,not CON_CLIPB
			or  console,CON_WIN95
		.endif
	.endif
dummy:	xor	eax,eax
	ret

pragma_init Install,6

endif
	END
