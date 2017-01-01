include stdlib.inc
include string.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

qsort	PROC USES rsi rdi rbx p:PVOID, n:SIZE_T, w:SIZE_T, compare:PVOID
	mov	rax,n
	cmp	rax,1
	jbe	toend
	dec	rax
	mul	w
	mov	rsi,p
	lea	rdi,[rsi+rax]
	push	0
recurse:
	mov	rcx,w
	lea	rax,[rdi+rcx]	; middle from (hi - lo) / 2
	sub	rax,rsi
	jz	@F
	sub	rdx,rdx
	div	rcx
	shr	rax,1
	mul	rcx
     @@:
	lea	rbx,[rsi+rax]

	push	rbx
	push	rsi
	call	compare
	cmp	rax,0
	jle	@F
	memxchg( rbx, rsi, w )
     @@:
	push	rdi
	push	rsi
	call	compare
	cmp	rax,0
	jle	@F
	memxchg( rdi, rsi, w )
     @@:
	push	rdi
	push	rbx
	call	compare
	cmp	rax,0
	jle	@F
	memxchg( rbx, rdi, w )
     @@:
	mov	p,rsi
	mov	n,rdi
lup:
	mov	rax,w
	add	p,rax
	cmp	p,rdi
	jae	@F
	push	rbx
	push	p
	call	compare
	cmp	rax,0
	jle	lup
     @@:
	mov	rax,w
	sub	n,rax
	cmp	n,rbx
	jbe	@F
	push	rbx
	push	n
	call	compare
	cmp	rax,0
	jg	@B
     @@:
	mov	rax,p
	cmp	n,rax
	jb	break
	memxchg( n, p, w )
	cmp	rbx,n
	jne	lup
	mov	rbx,p
	jmp	lup
break:
	mov	rax,w
	add	n,rax
     @@:
	mov	rax,w
	sub	n,rax
	cmp	n,rsi
	jbe	recursion
	push	rbx
	push	n
	call	compare
	test	rax,rax
	jz	@B
recursion:
	mov	rax,n
	sub	rax,rsi
	mov	rcx,rdi
	sub	rcx,p
	cmp	rax,rcx
	jl	lower
	cmp	rsi,n
	jae	@F
	pop	rax
	push	rsi
	push	n
	inc	rax
	push	rax
     @@:
	cmp	p,rdi
	jae	pending
	mov	rsi,p
	jmp	recurse
lower:
	cmp	p,rdi
	jae	@F
	pop	rax
	push	p
	push	rdi
	inc	rax
	push	rax
     @@:
	cmp	rsi,n
	jae	pending
	mov	rdi,n
	jmp	recurse
pending:
	pop	rax
	test	rax,rax
	jz	toend
	dec	rax
	pop	rdi
	pop	rsi
	push	rax
	jmp	recurse
toend:
	ret
qsort	ENDP

	END
