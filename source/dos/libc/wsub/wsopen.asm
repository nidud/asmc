; WSOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include string.inc
include alloc.inc

	.code

wsopen	PROC _CType PUBLIC USES bx wsub:DWORD
	les	bx,wsub
	mov	ax,es:[bx].S_WSUB.ws_maxfb
	shl	ax,2
	push	ax
	invoke	malloc,ax
	pop	cx
	les	bx,wsub
	stom	es:[bx].S_WSUB.ws_fcb
	jz	wsopen_end
	invoke	memzero,dx::ax,cx
	inc	ax
    wsopen_end:
	ret
wsopen	ENDP

	END
