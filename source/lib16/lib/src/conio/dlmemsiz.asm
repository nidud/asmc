; DLMEMSIZ.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

dlmemsize PROC _CType PUBLIC USES bx dobj:DWORD
	les	bx,dobj
	sub	cx,cx
	mov	cl,es:[bx].S_DOBJ.dl_count
	les	bx,es:[bx].S_DOBJ.dl_object
	sub	ax,ax
	.while cx
	    add al,es:[bx].S_TOBJ.to_count
	    add bx,16
	    dec cx
	.endw
	les	bx,dobj
	mov	dx,1
	add	dl,es:[bx].S_DOBJ.dl_count
	add	ax,dx
	shl	ax,4
	push	ax
	invoke	rcmemsize,DWORD PTR es:[bx].S_DOBJ.dl_rect,es:[bx].S_DOBJ.dl_flag
	pop	dx
	add	ax,dx
	ret
dlmemsize ENDP

	END
