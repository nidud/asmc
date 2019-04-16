; SETWINDOWPOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include crtl.inc
include winuser.inc

if(WINVER LT 0x0500)

	.data
	externdef user32_dll:BYTE
	SetWindowPos SetWindowPos_T dummy
	.code

dummy	proc WINAPI private
	xor	eax,eax
	ret	28
dummy	endp

Install:
	.if GetModuleHandle( addr user32_dll )

		.if GetProcAddress( eax, "SetWindowPos" )

			mov SetWindowPos,eax
		.endif
	.endif
	ret

.pragma init(Install, 6)

endif

	END
