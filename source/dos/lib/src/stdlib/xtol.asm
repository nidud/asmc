; XTOL.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc

	.code

xtol	PROC _CType PUBLIC USES bx cx string:PTR BYTE
	les	bx,string
	sub	ax,ax
	mov	cx,ax
	mov	dx,ax
    xtol_do:
	mov	al,es:[bx]
	or	al,20h
	inc	bx
	cmp	al,'0'
	jb	xtol_end
	cmp	al,'f'
	ja	xtol_end
	cmp	al,'9'
	ja	xtol_ch
	sub	al,'0'
	jmp	xtol_add
    xtol_ch:
	cmp	al,'a'
	jb	xtol_end
	sub	al,87
    xtol_add:
	shl	dx,4
	push	cx
	shr	ch,4
	or	dl,ch
	pop	cx
	shl	cx,4
	add	cx,ax
	adc	dx,0
	jmp	xtol_do
    xtol_end:
	mov	ax,cx
	ret
xtol	ENDP

	END
