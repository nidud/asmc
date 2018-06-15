include malloc.inc
include errno.inc

_FREE	equ 0
_USED	equ 1
_ALIGN	equ 3

	.data

	_heap_base PVOID 0	; address of main memory block
	_heap_free PVOID 0	; address of free memory block

	option stackbase:esp

	.code

malloc	PROC byte_count:UINT

	mov	ecx,byte_count
	add	ecx,sizeof(S_HEAP)+_GRANULARITY-1
	and	ecx,-(_GRANULARITY)

	mov	edx,_heap_free
	test	edx,edx
	jz	create_heap

	cmp	[edx].S_HEAP.h_type,_FREE
	mov	eax,[edx].S_HEAP.h_size
	jne	find_block
	cmp	eax,ecx
	jb	find_block

block_found:

	mov	[edx].S_HEAP.h_type,_USED
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
	ret

find_block:
	cmp	ecx,_amblksiz
	ja	create_heap

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
	add	eax,sizeof(S_HEAP)
	cmp	eax,ecx
	jae	@F
	mov	eax,ecx
@@:
	add	eax,sizeof(S_HEAP)
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
	mov	[eax+edx].S_HEAP.h_size,0
	mov	[eax+edx].S_HEAP.h_type,_USED
	mov	[eax+edx].S_HEAP.h_prev,eax
	mov	edx,_heap_base
	mov	[eax].S_HEAP.h_prev,edx
	.if	edx
		.while [edx].S_HEAP.h_next
		    mov edx,[edx].S_HEAP.h_next
		.endw
		mov [edx].S_HEAP.h_next,eax
		mov [eax].S_HEAP.h_prev,edx
	.else
		mov _heap_base,eax
	.endif
	mov	_heap_free,eax
	mov	edx,eax
	mov	eax,[edx].S_HEAP.h_size
	cmp	eax,ecx
	jae	block_found
nomem:
	mov	errno,ENOMEM
	xor	eax,eax
	jmp	toend
malloc	ENDP

free	proc uses eax maddr:PVOID
	mov	eax,maddr
	sub	eax,sizeof(S_HEAP)
	js	toend
	cmp	[eax].S_HEAP.h_type,_ALIGN
	jne	@F
	mov	eax,[eax].S_HEAP.h_prev
@@:
	cmp	[eax].S_HEAP.h_type,_USED
	jne	toend
	mov	[eax].S_HEAP.h_type,_FREE
	mov	ecx,[eax].S_HEAP.h_size
@@:
	cmp	[eax+ecx].S_HEAP.h_type,_FREE
	jne	@F
	add	ecx,[eax+ecx].S_HEAP.h_size
	mov	[eax].S_HEAP.h_size,ecx
	jmp	@B
@@:
	mov	_heap_free,eax
	cmp	[eax+ecx].S_HEAP.h_size,0
	jne	toend
	mov	eax,[eax+ecx].S_HEAP.h_prev
	cmp	[eax].S_HEAP.h_type,_FREE
	jne	toend
	mov	ecx,[eax].S_HEAP.h_size
@@:
	cmp	[eax+ecx].S_HEAP.h_type,_FREE
	jne	@F
	add	ecx,[eax+ecx].S_HEAP.h_size
	mov	[eax].S_HEAP.h_size,ecx
	jmp	@B
@@:
	cmp	[eax+ecx].S_HEAP.h_size,0
	jne	toend
	push	eax
	;
	; unlink the node
	;
	mov ecx,[eax].S_HEAP.h_prev
	mov edx,[eax].S_HEAP.h_next
	.if ecx
	    mov [ecx].S_HEAP.h_next,edx
	.endif
	.if edx
	    mov [edx].S_HEAP.h_prev,ecx
	.endif
	mov edx,_heap_base
	.if eax == edx
	    xor edx,edx
	    mov _heap_base,edx
	.endif
	mov	_heap_free,edx
	push	0
	call	GetProcessHeap
	push	eax
	call	HeapFree
toend:
	ret
free	ENDP

	END
