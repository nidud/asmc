; WSFFIRST.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include fblk.inc

	.code

wsffirst PROC _CType PUBLIC wsub:DWORD
	push	bx
	les	bx,wsub
	invoke	fbffirst,es:[bx].S_WSUB.ws_fcb,es:[bx].S_WSUB.ws_count
	pop	bx
	ret
wsffirst ENDP

	END
