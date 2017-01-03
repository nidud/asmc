; DLCLOSE.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc

	.code

dlclose PROC _CType PUBLIC USES bx dobj:DWORD
	push	ax
	invoke	dlhide,dobj
	push	ax
	les	bx,dobj
	invoke	rcclose,DWORD PTR es:[bx].S_DOBJ.dl_rect,es:[bx].S_DOBJ.dl_flag,es:[bx].S_DOBJ.dl_wp
	push	ax
	les	bx,dobj
	mov	ax,es:[bx].S_DOBJ.dl_flag
	and	ax,_D_MYBUF or _D_RCNEW
	.if ZERO?
	    mov WORD PTR es:[bx].S_DOBJ.dl_wp,ax
	    mov WORD PTR es:[bx].S_DOBJ.dl_wp+2,ax
	.endif
	.if ax & _D_RCNEW
	    invoke free,es::bx
	.else
	    and es:[bx].S_DOBJ.dl_flag,not _D_DOPEN
	.endif
	pop ax		; if open
	pop cx		; if visible
	pop dx		; AX on init
	ret
dlclose ENDP

	END
