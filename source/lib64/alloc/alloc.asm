include malloc.inc
include errno.inc

_FREE	equ 0
_USED	equ 1
_ALIGN	equ 3

	.data

	_heap_base dq 0		; address of main memory block
	_heap_free dq 0		; address of free memory block

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

malloc	PROC byte_count:SIZE_T

	add	rcx,sizeof(S_HEAP)+_GRANULARITY-1
	and	cl,-(_GRANULARITY)

	mov	rdx,_heap_free
	test	rdx,rdx
	jz	create_heap

	cmp	[rdx].S_HEAP.h_type,_FREE
	mov	rax,[rdx].S_HEAP.h_size
	jne	find_block
	cmp	rax,rcx
	jb	find_block

block_found:

	mov	[rdx].S_HEAP.h_type,_USED
	je	@F			; same size ?

	mov	[rdx].S_HEAP.h_size,rcx
	sub	rax,rcx			; create new free block
	mov	[rdx+rcx].S_HEAP.h_size,rax
	mov	[rdx+rcx].S_HEAP.h_type,_FREE
@@:
	lea	rax,[rdx+sizeof(S_HEAP)]; return address of memory block
	add	rdx,[rdx].S_HEAP.h_size
	mov	_heap_free,rdx
toend:
	ret

find_block:
	cmp	ecx,_amblksiz
	ja	create_heap

	mov	rdx,_heap_base
	xor	rax,rax
lupe:
	add	rdx,rax
	mov	rax,[rdx].S_HEAP.h_size
	test	rax,rax
	jz	last
	cmp	[rdx].S_HEAP.h_type,_FREE
	jne	lupe
	cmp	rax,rcx
	jae	block_found
	cmp	[rdx+rax].S_HEAP.h_type,_FREE
	jne	lupe
merge:
	add	rax,[rdx+rax].S_HEAP.h_size
	mov	[rdx].S_HEAP.h_size,rax
	cmp	[rdx+rax].S_HEAP.h_type,_FREE
	je	merge
	cmp	rax,rcx
	jb	lupe
	jmp	block_found
last:
	mov	rdx,[rdx].S_HEAP.h_prev
	mov	rdx,[rdx].S_HEAP.h_prev
	test	rdx,rdx
	jnz	lupe

create_heap:
	mov	eax,_amblksiz
	add	eax,sizeof(S_HEAP)
	cmp	eax,ecx
	jae	@F
	mov	eax,ecx
@@:
	add	eax,sizeof(S_HEAP)
	push	rcx
	push	rbx
	mov	rbx,rax
	sub	rsp,28h
	HeapAlloc( GetProcessHeap(), 0, rbx )
	add	rsp,28h
	mov	rdx,rbx
	pop	rbx
	pop	rcx
	test	rax,rax
	jz	nomem
	xor	r8,r8
	sub	rdx,sizeof(S_HEAP)
	mov	[rax].S_HEAP.h_size,rdx
	mov	[rax+8],r8;.S_HEAP.h_type,_FREE
	mov	[rax].S_HEAP.h_next,r8
	mov	[rax].S_HEAP.h_prev,r8
	mov	[rax+rdx].S_HEAP.h_size,r8
	mov	[rax+rdx].S_HEAP.h_type,_USED
	mov	[rax+rdx].S_HEAP.h_prev,rax
	mov	rdx,_heap_base
	.if	rdx
		.while [rdx].S_HEAP.h_next != r8
		    mov rdx,[rdx].S_HEAP.h_next
		.endw
		mov [rdx].S_HEAP.h_next,rax
		mov [rax].S_HEAP.h_prev,rdx
	.else
		mov _heap_base,rax
	.endif
	mov	_heap_free,rax
	mov	rdx,rax
	mov	rax,[rdx].S_HEAP.h_size
	cmp	rax,rcx
	jae	block_found
nomem:
	mov	errno,ENOMEM
	xor	rax,rax
	jmp	toend
malloc	ENDP

free	PROC maddr:PVOID
	push	rax
	mov	rax,rcx
	sub	rax,sizeof(S_HEAP)
	js	toend
	cmp	[rax].S_HEAP.h_type,_ALIGN
	jne	@F
	mov	rax,[rax].S_HEAP.h_prev
@@:
	cmp	[rax].S_HEAP.h_type,_USED
	jne	toend
	xor	rdx,rdx
	mov	[rax+8],rdx
	mov	rcx,[rax].S_HEAP.h_size
@@:
	cmp	[rax+rcx].S_HEAP.h_type,dl;_FREE
	jne	@F
	add	rcx,[rax+rcx].S_HEAP.h_size
	mov	[rax].S_HEAP.h_size,rcx
	jmp	@B
@@:
	mov	_heap_free,rax
	cmp	[rax+rcx].S_HEAP.h_size,rdx
	jne	toend
	mov	rax,[rax+rcx].S_HEAP.h_prev
	cmp	[rax].S_HEAP.h_type,dl;_FREE
	jne	toend
	mov	rcx,[rax].S_HEAP.h_size
@@:
	cmp	[rax+rcx].S_HEAP.h_type,dl;_FREE
	jne	@F
	add	rcx,[rax+rcx].S_HEAP.h_size
	mov	[rax].S_HEAP.h_size,rcx
	jmp	@B
@@:
	cmp	[rax+rcx].S_HEAP.h_size,rdx
	jne	toend
	push	rbx
	mov	rbx,rax
	;
	; unlink the node
	;
	mov rcx,[rax].S_HEAP.h_prev
	mov rax,[rax].S_HEAP.h_next
	.if rcx
	    mov [rcx].S_HEAP.h_next,rax
	.endif
	.if rax
	    mov [rax].S_HEAP.h_prev,rcx
	.endif
	mov rax,_heap_base
	.if rax == rbx
	    xor rax,rax
	    mov _heap_base,rax
	.endif
	mov	_heap_free,rax
	sub	rsp,28h
	HeapFree(GetProcessHeap(), 0, rbx)
	add	rsp,28h
	pop	rbx
toend:
	pop	rax
	ret
free	ENDP

	END
