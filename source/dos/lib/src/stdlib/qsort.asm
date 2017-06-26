; QSORT.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc

	.code

qsort	PROC _CType PUBLIC USES si di bx p:DWORD, n:WORD, w:WORD, compare:DWORD
	mov	ax,n
	cmp	ax,1
	ja	@F
	jmp	toend
     @@:
	dec	ax
	mul	w
	les	si,p
	mov	di,ax
	add	di,si
	push	0
recurse:
	mov	cx,w
	mov	ax,di
	add	ax,cx
	sub	ax,si
	jz	@F
	sub	dx,dx
	div	cx
	shr	ax,1
	mul	cx
     @@:
	add	ax,si
	mov	bx,ax

	mov	ax,WORD PTR p[2]
	push	bx
	push	ax
	push	si
	push	ax
	push	bx
	call	compare
	pop	bx
	cmp	ax,0
	jle	@F
	mov	ax,WORD PTR p[2]
	invoke	memxchg,ax::bx,ax::si,w
     @@:
	mov	ax,WORD PTR p[2]
	push	bx
	push	ax
	push	si
	push	ax
	push	di
	call	compare
	pop	bx
	cmp	ax,0
	jle	@F
	mov	ax,WORD PTR p[2]
	invoke	memxchg,ax::di,ax::si,w
     @@:
	mov	ax,WORD PTR p[2]
	push	bx
	push	ax
	push	bx
	push	ax
	push	di
	call	compare
	pop	bx
	cmp	ax,0
	jle	@F
	mov	ax,WORD PTR p[2]
	invoke	memxchg,ax::bx,ax::di,w
     @@:
	mov	WORD PTR p,si
	mov	n,di
lup:
	mov	ax,w
	add	WORD PTR p,ax
	cmp	WORD PTR p,di
	jae	@F
	mov	ax,WORD PTR p[2]
	push	bx
	push	ax
	push	WORD PTR p
	push	ax
	push	bx
	call	compare
	pop	bx
	cmp	ax,0
	jle	lup
     @@:
	mov	ax,w
	sub	n,ax
	cmp	n,bx
	jbe	@F
	mov	ax,WORD PTR p[2]
	push	bx
	push	ax
	push	n
	push	ax
	push	bx
	call	compare
	pop	bx
	cmp	ax,0
	jg	@B
     @@:
	mov	ax,WORD PTR p
	cmp	n,ax
	jb	break
	mov	dx,WORD PTR p[2]
	mov	cx,n
	invoke	memxchg,dx::ax,dx::cx,w
	cmp	bx,n
	jne	lup
	mov	bx,WORD PTR p
	jmp	lup
break:
	mov	ax,w
	add	n,ax
     @@:
	mov	ax,w
	sub	n,ax
	cmp	n,si
	jbe	recursion
	mov	ax,WORD PTR p[2]
	push	bx
	push	ax
	push	n
	push	ax
	push	bx
	call	compare
	pop	bx
	test	ax,ax
	jz	@B
recursion:
	mov	ax,n
	sub	ax,si
	mov	cx,di
	sub	cx,WORD PTR p
	cmp	ax,cx
	jl	lower
	cmp	si,n
	jae	@F
	pop	ax
	push	si
	push	n
	inc	ax
	push	ax
     @@:
	cmp	WORD PTR p,di
	jae	pending
	mov	si,WORD PTR p
	jmp	recurse
lower:
	cmp	WORD PTR p,di
	jae	@F
	pop	ax
	push	WORD PTR p
	push	di
	inc	ax
	push	ax
     @@:
	cmp	si,n
	jae	pending
	mov	di,n
	jmp	recurse
pending:
	pop	ax
	test	ax,ax
	jz	toend
	dec	ax
	pop	di
	pop	si
	push	ax
	jmp	recurse
toend:
	ret
qsort	ENDP

	END
