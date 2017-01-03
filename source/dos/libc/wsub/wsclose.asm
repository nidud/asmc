; WSCLOSE.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include alloc.inc

	.code

wsclose PROC _CType PUBLIC wsub:DWORD
	invoke	wsfree,wsub
	push	ax
	push	bx
	mov	bx,WORD PTR wsub
	pushm	[bx].S_WSUB.ws_fcb
	mov	WORD PTR [bx].S_WSUB.ws_fcb,0
	call	free
	pop	bx
	pop	ax
	ret
wsclose ENDP

	END
