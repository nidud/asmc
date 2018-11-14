; GETFOREGROUNDWINDOW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

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

dummy	proc WINAPI private
	xor	eax,eax
	ret
dummy	endp

.pragma(init(Install, 6))

endif
	END
