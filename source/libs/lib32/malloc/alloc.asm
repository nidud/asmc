; ALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

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
	add	ecx,HEAP+_GRANULARITY-1
	and	ecx,-(_GRANULARITY)

	mov	edx,_heap_free
	test	edx,edx
	jz	create_heap

	cmp	[edx].HEAP.type,_FREE
	mov	eax,[edx].HEAP.size
	jne	find_block
	cmp	eax,ecx
	jb	find_block

block_found:

	mov	[edx].HEAP.type,_USED
	je	@F			; same size ?

	mov	[edx].HEAP.size,ecx
	sub	eax,ecx			; create new free block
	mov	[edx+ecx].HEAP.size,eax
	mov	[edx+ecx].HEAP.type,_FREE
@@:
	lea	eax,[edx+HEAP]		; return address of memory block
	add	edx,[edx].HEAP.size
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
	mov	eax,[edx].HEAP.size
	test	eax,eax
	jz	last
	cmp	[edx].HEAP.type,_FREE
	jne	lupe
	cmp	eax,ecx
	jae	block_found
	cmp	[edx+eax].HEAP.type,_FREE
	jne	lupe
merge:
	add	eax,[edx+eax].HEAP.size
	mov	[edx].HEAP.size,eax
	cmp	[edx+eax].HEAP.type,_FREE
	je	merge
	cmp	eax,ecx
	jb	lupe
	jmp	block_found
last:
	mov	edx,[edx].HEAP.prev
	mov	edx,[edx].HEAP.prev
	test	edx,edx
	jnz	lupe

create_heap:
	mov	eax,_amblksiz
	add	eax,HEAP
	cmp	eax,ecx
	jae	@F
	mov	eax,ecx
@@:
	add	eax,HEAP
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
	sub	edx,HEAP
	mov	[eax].HEAP.size,edx
	mov	[eax].HEAP.type,_FREE
	mov	[eax].HEAP.next,0
	mov	[eax+edx].HEAP.size,0
	mov	[eax+edx].HEAP.type,_USED
	mov	[eax+edx].HEAP.prev,eax
	mov	edx,_heap_base
	mov	[eax].HEAP.prev,edx
	.if	edx
		.while [edx].HEAP.next
		    mov edx,[edx].HEAP.next
		.endw
		mov [edx].HEAP.next,eax
		mov [eax].HEAP.prev,edx
	.else
		mov _heap_base,eax
	.endif
	mov	_heap_free,eax
	mov	edx,eax
	mov	eax,[edx].HEAP.size
	cmp	eax,ecx
	jae	block_found
nomem:
	mov	errno,ENOMEM
	xor	eax,eax
	jmp	toend
malloc	ENDP

free	proc uses eax maddr:ptr
	mov	eax,maddr
	sub	eax,HEAP
	js	toend
	cmp	[eax].HEAP.type,_ALIGN
	jne	@F
	mov	eax,[eax].HEAP.prev
@@:
	cmp	[eax].HEAP.type,_USED
	jne	toend
	mov	[eax].HEAP.type,_FREE
	mov	ecx,[eax].HEAP.size
@@:
	cmp	[eax+ecx].HEAP.type,_FREE
	jne	@F
	add	ecx,[eax+ecx].HEAP.size
	mov	[eax].HEAP.size,ecx
	jmp	@B
@@:
	mov	_heap_free,eax
	cmp	[eax+ecx].HEAP.size,0
	jne	toend
	mov	eax,[eax+ecx].HEAP.prev
	cmp	[eax].HEAP.type,_FREE
	jne	toend
	mov	ecx,[eax].HEAP.size
@@:
	cmp	[eax+ecx].HEAP.type,_FREE
	jne	@F
	add	ecx,[eax+ecx].HEAP.size
	mov	[eax].HEAP.size,ecx
	jmp	@B
@@:
	cmp	[eax+ecx].HEAP.size,0
	jne	toend
	push	eax
	;
	; unlink the node
	;
	mov ecx,[eax].HEAP.prev
	mov edx,[eax].HEAP.next
	.if ecx
	    mov [ecx].HEAP.next,edx
	.endif
	.if edx
	    mov [edx].HEAP.prev,ecx
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
