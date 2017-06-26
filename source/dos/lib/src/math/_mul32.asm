; _MUL32.ASM--
; Copyright (C) 2015 Doszip Developers

include libc.inc
include math.inc

PUBLIC	__U4M
PUBLIC	__I4M

.code	; dx:ax * cx:bx

__U4M:
__I4M:
_mul32	PROC _CType PUBLIC
	push	bp
	push	si
	push	di
	push	ax
	push	dx
	push	dx
	mul	bx	; 1L * 2L
	mov	si,dx
	mov	di,ax
	pop	ax
	mul	cx	; 1H * 2H
	mov	bp,dx
	xchg	bx,ax
	pop	dx
	mul	dx	; 1H * 2L
	add	si,ax
	adc	bx,dx
	pop	ax
	mul	cx	; 1L * 2H
	add	si,ax
	adc	bx,dx
	adc	bp,0
	mov	cx,bp
	mov	dx,si
	mov	ax,di
	pop	di
	pop	si
	pop	bp
	ret	; cx:bx:dx:ax
_mul32	ENDP

	END
