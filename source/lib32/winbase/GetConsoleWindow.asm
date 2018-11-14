; GETCONSOLEWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include crtl.inc
include winbase.inc

if(_WIN32_WINNT LT 0x0500)

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

.pragma(init(Install, 6))

endif
	END
