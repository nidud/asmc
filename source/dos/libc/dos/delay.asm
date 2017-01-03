; DELAY.ASM--
; Copyright (C) 2015 Doszip Developers

include dos.inc
include math.inc

	.code

delay PROC _CType PUBLIC USES bx time:size_t
	push	si
	push	di
ifdef __3__
	movzx	eax,time
	mul	cs:T1
	shld	edx,eax,16
else
	lodm	cs:T1
	xor	cx,cx
	mov	bx,time
	call	_mul32
endif
	mov	si,dx
	mov	di,ax
	call	read_timer
	mov	bx,dx
	add	di,dx
	adc	si,0
	jmp	delay_02
    delay_loop:
	cmp	dx,bx
	jnb	delay_01
	or	si,si
	jz	delay_end
	sub	si,1
	sbb	di,0
    delay_01:
	mov	bx,dx
    delay_02:
	call	read_timer
	or	si,si
	jnz	delay_loop
	cmp	dx,di
	jb	delay_loop
    delay_end:
	pop	di
	pop	si
	ret
delay ENDP

T1 dd ?

dummy:	push	si
	push	di
	pop	di
	pop	si
	ret

read_timer:
	pushf
	cli
	xor	ax,ax
	out	43h,al
	call	dummy
	in	al,40h
	mov	dl,al
	call	dummy
	in	al,40h
	mov	dh,al
	not	dx
	popf
	ret

Install:
	mov	cx,100
      @@:
	call	read_timer
	and	dx,1
	jz	@F
	dec	cx
	jnz	@B
	mov	WORD PTR cs:T1,2*1193
	mov	WORD PTR cs:T1+2,cx
	ret
      @@:
	mov	WORD PTR cs:T1,1193
	mov	WORD PTR cs:T1+2,dx
	ret

_TEXT	ENDS

pragma_init Install, 9

	END
