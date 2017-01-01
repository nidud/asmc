include alloc.inc
include errno.inc

_FREE	equ 0
_LOCAL	equ 1
_GLOBAL equ 2
_ALIGNX equ 3

	.data

	_heap_base dq 0		; address of main memory block
	_heap_free dq 0		; address of free memory block

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

malloc	PROC byte_count:SIZE_T

	add	rcx,sizeof(S_HEAP)+_GRANULARITY-1
	and	rcx,-(_GRANULARITY)

	mov	rdx,_heap_free
	test	rdx,rdx
	jz	create_heap

	cmp	[rdx].S_HEAP.h_type,_FREE
	mov	rax,[rdx].S_HEAP.h_size
	jne	find_block
	cmp	rax,rcx
	jb	find_block

block_found:

	mov	[rdx].S_HEAP.h_type,_LOCAL
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
	test	eax,eax
	jz	h_alloc
	cmp	rax,rcx
	jb	h_alloc
	add	rax,sizeof(S_HEAP) * 2

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
	sub	rdx,sizeof(S_HEAP)
	mov	[rax].S_HEAP.h_size,rdx
	mov	[rax].S_HEAP.h_type,_FREE
	mov	[rax].S_HEAP.h_next,0
	add	rdx,rax
	mov	[rdx].S_HEAP.h_size,0
	mov	[rdx].S_HEAP.h_type,_LOCAL
	mov	[rdx].S_HEAP.h_prev,rax
	mov	rdx,_heap_base
	mov	[rax].S_HEAP.h_prev,rdx
	.if	rdx
		push	rcx
		mov	rcx,[rdx].S_HEAP.h_next
		mov	[rdx].S_HEAP.h_next,rax
		mov	[rax].S_HEAP.h_next,rcx
		.if	rcx
			mov [rcx].S_HEAP.h_prev,rax
		.endif
		pop	rcx
	.endif
	mov	_heap_free,rax
	mov	_heap_base,rax
	mov	rdx,rax
	mov	rax,[rdx].S_HEAP.h_size
	cmp	rax,rcx
	jae	block_found
nomem:
	mov	errno,ENOMEM
	xor	rax,rax
	jmp	toend
h_alloc:
	push	rcx
	push	rbx
	mov	rbx,rcx
	sub	rsp,28h
	HeapAlloc( GetProcessHeap(), 0, rbx )
	add	rsp,28h
	pop	rbx
	pop	rcx
	test	rax,rax
	jz	nomem
	mov	[rax].S_HEAP.h_size,rcx
	mov	[rax].S_HEAP.h_type,_GLOBAL
	mov	rcx,_heap_base
	mov	[rax].S_HEAP.h_prev,rcx
	mov	[rax].S_HEAP.h_next,rcx
	.if	rcx
		mov rdx,[rcx].S_HEAP.h_next
		mov [rcx].S_HEAP.h_next,rax
		mov [rax].S_HEAP.h_next,rdx
		.if rdx
			mov [rdx].S_HEAP.h_prev,rax
		.endif
	.endif
	add	rax,sizeof(S_HEAP)
	jmp	toend
malloc	ENDP

free	PROC maddr:PVOID
	push	rax
aligned:
	mov	rax,rcx
	sub	rax,sizeof(S_HEAP)
	js	toend
	cmp	[rax].S_HEAP.h_type,_LOCAL
	jne	h_free
	mov	[rax].S_HEAP.h_type,_FREE
	mov	_heap_free,rax
toend:
	pop	rax
	ret
h_free:
	cmp	[rax].S_HEAP.h_type,_ALIGNX
	mov	rcx,[rax].S_HEAP.h_prev
	je	aligned
	cmp	[rax].S_HEAP.h_type,_GLOBAL
	jne	toend
	push	rdx
	mov	rdx,[rax].S_HEAP.h_prev
	mov	rcx,[rax].S_HEAP.h_next
	.if	rdx
		mov [rdx].S_HEAP.h_next,rcx
	.endif
	.if	rcx
		mov [rcx].S_HEAP.h_prev,rdx
	.endif
	push	rbx
	mov	rbx,rax
	sub	rsp,20h
	HeapFree( GetProcessHeap(), 0, rbx )
	add	rsp,20h
	pop	rbx
	pop	rdx
	pop	rax
	ret
free	ENDP

	END
