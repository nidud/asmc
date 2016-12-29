include stdlib.inc
include string.inc

	.code

qsort	PROC USES esi edi ebx p:PVOID, n:SIZE_T, w:SIZE_T, compare:PVOID
	mov	eax,n
	cmp	eax,1
	jbe	toend
	dec	eax
	mul	w
	mov	esi,p
	lea	edi,[esi+eax]
	push	0
recurse:
	mov	ecx,w
	lea	eax,[edi+ecx]	; middle from (hi - lo) / 2
	sub	eax,esi
	jz	@F
	sub	edx,edx
	div	ecx
	shr	eax,1
	mul	ecx
     @@:
	lea	ebx,[esi+eax]

	push	ebx
	push	esi
	call	compare
	cmp	eax,0
	jle	@F
	memxchg( ebx, esi, w )
     @@:
	push	edi
	push	esi
	call	compare
	cmp	eax,0
	jle	@F
	memxchg( edi, esi, w )
     @@:
	push	edi
	push	ebx
	call	compare
	cmp	eax,0
	jle	@F
	memxchg( ebx, edi, w )
     @@:
	mov	p,esi
	mov	n,edi
lup:
	mov	eax,w
	add	p,eax
	cmp	p,edi
	jae	@F
	push	ebx
	push	p
	call	compare
	cmp	eax,0
	jle	lup
     @@:
	mov	eax,w
	sub	n,eax
	cmp	n,ebx
	jbe	@F
	push	ebx
	push	n
	call	compare
	cmp	eax,0
	jg	@B
     @@:
	mov	eax,p
	cmp	n,eax
	jb	break
	memxchg( n, p, w )
	cmp	ebx,n
	jne	lup
	mov	ebx,p
	jmp	lup
break:
	mov	eax,w
	add	n,eax
     @@:
	mov	eax,w
	sub	n,eax
	cmp	n,esi
	jbe	recursion
	push	ebx
	push	n
	call	compare
	test	eax,eax
	jz	@B
recursion:
	mov	eax,n
	sub	eax,esi
	mov	ecx,edi
	sub	ecx,p
	cmp	eax,ecx
	jl	lower
	cmp	esi,n
	jae	@F
	pop	eax
	push	esi
	push	n
	inc	eax
	push	eax
     @@:
	cmp	p,edi
	jae	pending
	mov	esi,p
	jmp	recurse
lower:
	cmp	p,edi
	jae	@F
	pop	eax
	push	p
	push	edi
	inc	eax
	push	eax
     @@:
	cmp	esi,n
	jae	pending
	mov	edi,n
	jmp	recurse
pending:
	pop	eax
	test	eax,eax
	jz	toend
	dec	eax
	pop	edi
	pop	esi
	push	eax
	jmp	recurse
toend:
	ret
qsort	ENDP

	END
