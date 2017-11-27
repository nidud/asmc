; WSFBLK.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include fblk.inc

	.code

wsfblk	PROC _CType PUBLIC wsub:DWORD, index:size_t
	mov	ax,index
	push	bx
	les	bx,wsub
	cmp	es:[bx],ax
	jle	wsfblk_err
	les	bx,es:[bx].S_WSUB.ws_fcb
	shl	ax,2
	add	bx,ax		; ZF - clear
	les	bx,es:[bx]
	mov	cx,es:[bx]	; CX fblk.flag
	mov	dx,es		; DX:AX fblk
	mov	ax,bx
    wsfblk_end:
	pop	bx
	ret
    wsfblk_err:
	sub	ax,ax
	cwd
	jmp	wsfblk_end
wsfblk	ENDP

	END
