; ATOL.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc

	.code

atol PROC _CType PUBLIC USES bx cx si di string:PTR BYTE
	push	es
	les	bx,string
	sub	cx,cx
      @@:
	mov	cl,es:[bx]
	inc	bx
	cmp	cl,' '
	je	@B
	push	cx
	cmp	cl,'-'
	je	@F
	cmp	cl,'+'
	jne	atol_set
      @@:
	mov	cl,es:[bx]
	inc	bx
    atol_set:
	sub	ax,ax
	sub	dx,dx
    atol_loop:
	sub	cl,'0'
	jc	@F
	cmp	cl,9
	ja	@F
	mov	si,dx
	mov	di,ax
ifdef __16__
	shl	ax,1
	rcl	dx,1
	shl	ax,1
	rcl	dx,1
	shl	ax,1
	rcl	dx,1
else
	shl	dx,3
	shld	ax,dx,3
endif
	add	ax,di
	adc	dx,si
	add	ax,di
	adc	dx,si
	add	ax,cx
	adc	dx,0
	mov	cl,es:[bx]
	inc	bx
	jmp	atol_loop
      @@:
	pop	cx
	cmp	cl,'-'
	je	atol_neg
    atol_end:
	pop	es
	ret
    atol_neg:
	neg	ax
	neg	dx
	sbb	ax,0
	jmp	atol_end
atol	ENDP

	END
