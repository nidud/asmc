; RCREAD.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc
include mouse.inc

.code

rcread	PROC _CType PUBLIC USES bx si di rc:DWORD, wc:DWORD
local	lsize:	WORD
	push	ds
	xor	ax,ax
	mov	al,_scrcol
	add	ax,ax
	mov	lsize,ax
	HideMouseCursor
	invoke	rcsprc,rc
	mov	ds,dx
	mov	dx,ax
	les	di,wc
	mov	bx,di
	xor	ax,ax
	mov	cx,ax
	mov	al,rc.S_RECT.rc_col
	mov	ah,rc.S_RECT.rc_row
	cld?
    rcread_loop:
	mov	si,dx
	add	dx,lsize
	mov	cl,al
	rep	movsw
	dec	ah
	jnz	rcread_loop
	ShowMouseCursor
	mov	dx,es
	mov	ax,bx
	pop	ds
	ret
rcread	ENDP

	END
