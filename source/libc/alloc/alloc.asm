include alloc.inc
include errno.inc

_FREE	equ 0
_LOCAL	equ 1
_GLOBAL equ 2
_ALIGNX equ 3

	.data

	_heap_base dd 0		; address of main memory block
	_heap_free dd 0		; address of free memory block

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

malloc	PROC byte_count:UINT

	mov ecx,[esp+4] ; byte count to allocate
	add ecx,sizeof(S_HEAP)+_GRANULARITY-1
	and ecx,-(_GRANULARITY)

	mov edx,_heap_free
	test edx,edx
	jz  create_heap

	cmp [edx].S_HEAP.h_type,_FREE
	mov eax,[edx].S_HEAP.h_size
	jne find_block
	cmp eax,ecx
	jb  find_block

block_found:

	mov	[edx].S_HEAP.h_type,_LOCAL
	je	@F			; same size ?

	mov	[edx].S_HEAP.h_size,ecx
	sub	eax,ecx			; create new free block
	mov	[edx+ecx].S_HEAP.h_size,eax
	mov	[edx+ecx].S_HEAP.h_type,_FREE
@@:

	lea	eax,[edx+sizeof(S_HEAP)]; return address of memory block
	add	edx,[edx].S_HEAP.h_size
	mov	_heap_free,edx
toend:
	ret	4

find_block:
	mov	edx,_heap_base
	xor	eax,eax
lupe:
	add	edx,eax
	mov	eax,[edx].S_HEAP.h_size
	test	eax,eax
	jz	last
	cmp	[edx].S_HEAP.h_type,_FREE
	jne	lupe
	cmp	eax,ecx
	jae	block_found
	cmp	[edx+eax].S_HEAP.h_type,_FREE
	jne	lupe
merge:
	add	eax,[edx+eax].S_HEAP.h_size
	mov	[edx].S_HEAP.h_size,eax
	cmp	[edx+eax].S_HEAP.h_type,_FREE
	je	merge
	cmp	eax,ecx
	jb	lupe
	jmp	block_found
last:
	mov	edx,[edx].S_HEAP.h_prev
	mov	edx,[edx].S_HEAP.h_prev
	test	edx,edx
	jnz	lupe

create_heap:
	mov	eax,_amblksiz
	test	eax,eax
	jz	h_alloc
	cmp	eax,ecx
	jb	h_alloc
	add	eax,sizeof(S_HEAP) * 2
	push	eax
	push	ecx
	push	eax
	push	0
	call	GetProcessHeap
	push	eax
	call	HeapAlloc
	pop	ecx
	pop	edx
	test	eax,eax
	jz	nomem
	sub	edx,sizeof(S_HEAP)
	mov	[eax].S_HEAP.h_size,edx
	mov	[eax].S_HEAP.h_type,_FREE
	mov	[eax].S_HEAP.h_next,0
	add	edx,eax
	mov	[edx].S_HEAP.h_size,0
	mov	[edx].S_HEAP.h_type,_LOCAL
	mov	[edx].S_HEAP.h_prev,eax
	mov	edx,_heap_base
	mov	[eax].S_HEAP.h_prev,edx
	.if	edx
		push	ecx
		mov	ecx,[edx].S_HEAP.h_next
		mov	[edx].S_HEAP.h_next,eax
		mov	[eax].S_HEAP.h_next,ecx
		.if	ecx
			mov [ecx].S_HEAP.h_prev,eax
		.endif
		pop	ecx
	.endif
	mov	_heap_free,eax
	mov	_heap_base,eax
	mov	edx,eax
	mov	eax,[edx].S_HEAP.h_size
	cmp	eax,ecx
	jae	block_found
nomem:
	mov	errno,ENOMEM
	xor	eax,eax
	jmp	toend
h_alloc:
	push	ecx
	push	ecx
	push	0
	call	GetProcessHeap
	push	eax
	call	HeapAlloc
	pop	ecx
	test	eax,eax
	jz	nomem
	mov	[eax].S_HEAP.h_size,ecx
	mov	[eax].S_HEAP.h_type,_GLOBAL
	mov	ecx,_heap_base
	mov	[eax].S_HEAP.h_prev,ecx
	mov	[eax].S_HEAP.h_next,ecx
	.if	ecx
		mov edx,[ecx].S_HEAP.h_next
		mov [ecx].S_HEAP.h_next,eax
		mov [eax].S_HEAP.h_next,edx
		.if edx
			mov [edx].S_HEAP.h_prev,eax
		.endif
	.endif
	add	eax,16
	jmp	toend
malloc	ENDP

free	PROC maddr:PVOID
	push	eax
	mov	eax,[esp+8]
	sub	eax,sizeof(S_HEAP)
	js	toend
	cmp	[eax].S_HEAP.h_type,_LOCAL
	jne	h_free
	mov	[eax].S_HEAP.h_type,_FREE
	mov	_heap_free,eax
toend:
	pop	eax
	ret	4
h_free:
	cmp	[eax].S_HEAP.h_type,_GLOBAL
	jne	toend
	push	edx
	push	eax
	mov	edx,[eax].S_HEAP.h_prev
	mov	ecx,[eax].S_HEAP.h_next
	.if	edx
		mov [edx].S_HEAP.h_next,ecx
	.endif
	.if	ecx
		mov [ecx].S_HEAP.h_prev,edx
	.endif
	push	0
	call	GetProcessHeap
	push	eax
	call	HeapFree
	pop	edx
	pop	eax
	ret	4
free	ENDP

	END
