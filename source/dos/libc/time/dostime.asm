; DOSTIME.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

dostime PROC _CType PUBLIC
	push	cx
	mov	ah,2Ah
	int	21h
	mov	ax,cx
	sub	ax,DT_BASEYEAR
	shl	ax,9
	xchg	ax,dx
	mov	cl,al
	mov	al,ah
	xor	ah,ah
	shl	ax,5
	xchg	ax,dx
	or	ax,dx
	or	al,cl
	push	ax
	mov	ah,2Ch	; CH = hour
	int	21h	; CL = minute
	xor	ax,ax	; DH = second
	mov	al,dh
	shr	ax,1
	mov	dx,ax	; second/2
	mov	al,ch
	mov	ch,ah
	shl	cx,5
	shl	ax,11
	or	ax,cx
	or	ax,dx	; hhhhhmmmmmmsssss
	pop	dx
	pop	cx
	ret
dostime ENDP

	END
