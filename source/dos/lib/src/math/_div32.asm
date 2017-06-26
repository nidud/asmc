; _DIV32.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
include math.inc

PUBLIC	__I4D
PUBLIC	__U4D

.code	; dx:ax / cx:bx

__U4D:
__I4D:
_div32	PROC _CType PUBLIC
	test	cx,cx
	jnz	DIV_01
	test	dx,dx
	jz	DIV_00
	test	bx,bx
	jnz	DIV_01
DIV_00: div	bx
	mov	bx,dx
	xor	dx,dx
	mov	cx,dx
	ret
DIV_01: push	bp
	push	si
	push	di
	mov	bp,cx
	mov	cx,32
	xor	si,si
	xor	di,di
DIV_02: shl	ax,1
	rcl	dx,1
	rcl	si,1
	rcl	di,1
	cmp	di,bp
	jb	DIV_04
	ja	DIV_03
	cmp	si,bx
	jb	DIV_04
DIV_03: sub	si,bx
	sbb	di,bp
	inc	ax
DIV_04: dec	cx
	jnz	DIV_02
	mov	cx,di
	mov	bx,si
	pop	di
	pop	si
	pop	bp
	ret
_div32	ENDP

	END
