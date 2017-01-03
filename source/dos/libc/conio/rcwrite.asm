; RCWRITE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include mouse.inc

.code

rcwrite PROC _CType PUBLIC USES si di bx rc:DWORD, wc:DWORD
local lsize:WORD
	push	ds
	HideMouseCursor
	mov	ah,0
	mov	al,_scrcol
	add	ax,ax
	mov	lsize,ax
	invoke	rcsprc,rc
	mov	es,dx
	mov	dx,ax
	lds	si,wc
	mov	bx,si
	xor	ax,ax
	mov	cx,ax
	mov	al,rc.S_RECT.rc_col
	mov	ah,rc.S_RECT.rc_row
	cld?
    rcwrite_loop:
	mov	di,dx
	add	dx,lsize
	mov	cl,al
	rep	movsw
	dec	ah
	jnz	rcwrite_loop
	ShowMouseCursor
	mov	dx,ds
	mov	ax,bx
	pop	ds
	ret
rcwrite ENDP

	END
