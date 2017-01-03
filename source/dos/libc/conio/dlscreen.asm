; DLSCREEN.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

dlscreen PROC _CType PUBLIC USES bx dobj:DWORD, attrib:size_t
	les	bx,dobj
	sub	ax,ax
	mov	es:[bx],ax
	mov	es:[bx+2],ax	; index,count
	mov	es:[bx+4],ax	; x,y
	mov	dx,ax
	mov	al,_scrcol	; adapt to current screen
	mov	ah,_scrrow
	inc	ah
	mov	es:[bx+6],ax
	push	es
	invoke	rcopen,ax::dx,_D_CLEAR or _D_BACKG,attrib,0,0
	pop	es
	stom	es:[bx].S_DOBJ.dl_wp
	mov	es:[bx].S_DOBJ.dl_flag,_D_DOPEN
	mov	dx,es
	mov	ax,bx
	ret
dlscreen ENDP

	END
