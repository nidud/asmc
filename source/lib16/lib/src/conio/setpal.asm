; SETPAL.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

setpal	PROC _CType PUBLIC USES bx palid:size_t, clid:size_t
	test	console,CON_COLOR
	jz	setpal_end
	mov	ax,palid
	mov	dx,clid
	mov	ch,al
	mov	bx,dx
	mov	ax,0040h
	mov	es,ax
	mov	dx,es:[0063h]
	cmp	dx,03D4h
	jne	setpal_end
	cli
	mov	dx,03DAh
	in	al,dx
	mov	dx,03C0h
	mov	al,bl
	out	dx,al
	mov	al,ch
	out	dx,al
	mov	dx,03DAh
	in	al,dx
	mov	dx,03C0h
	mov	al,20h
	out	dx,al
	sti
    setpal_end:
	ret
setpal	ENDP

	END
