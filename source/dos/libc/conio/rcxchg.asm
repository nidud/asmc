; RCXCHG.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc
include mouse.inc

.code

rcxchg PROC _CType PUBLIC USES si di bx cx rc:DWORD, wc:DWORD
local lsize:size_t
	push	ds
	HideMouseCursor
	mov	ah,0
	mov	al,_scrcol
	add	ax,ax
	mov	lsize,ax
	invoke	rcsprc,rc
	mov	es,dx
	mov	di,ax
	mov	dx,ax
	mov	bx,WORD PTR [rc+2]
	lds	si,wc
	mov	ch,0
	cld?
    rcxchg_loopl:
	mov	di,dx
	add	dx,lsize
	mov	cl,bl
    rcxchg_loopc:
	mov	ax,es:[di]
	movsw
	mov	[si-2],ax
	dec	cx
	jnz	rcxchg_loopc
	dec	bh
	jnz	rcxchg_loopl
	ShowMouseCursor
	pop	ds
	ret
rcxchg	ENDP

	END
