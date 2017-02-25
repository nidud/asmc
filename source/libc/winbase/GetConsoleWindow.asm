include consx.inc
include crtl.inc
include winbase.inc

if(WINVER LT 0x0500)

	.data
	externdef kernel32_dll:BYTE
	GetConsoleWindow GetConsoleWindow_T dummy

	.code
Install:
	.if GetModuleHandle( addr kernel32_dll )
		.if GetProcAddress( eax, "GetConsoleWindow" )
			mov GetConsoleWindow,eax
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
