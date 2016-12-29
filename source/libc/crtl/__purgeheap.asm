include alloc.inc

	.code

__purgeheap PROC USES esi
	mov	edx,_heap_base
	.while	edx
		.while	[edx].S_HEAP.h_size
			.if	[edx].S_HEAP.h_type == 0
				mov	ecx,[edx].S_HEAP.h_size
				.while	[edx+ecx].S_HEAP.h_type == 0
					add ecx,[edx+ecx].S_HEAP.h_size
					mov [edx].S_HEAP.h_size,ecx
				.endw
			.endif
			add	edx,[edx].S_HEAP.h_size
		.endw
		mov	edx,[edx].S_HEAP.h_prev
		mov	edx,[edx].S_HEAP.h_prev
	.endw
	mov	edx,_heap_base
	.while	edx
		mov	ecx,[edx].S_HEAP.h_size
		.if	![ecx+edx].S_HEAP.h_size && ![edx].S_HEAP.h_type
			mov	[edx].S_HEAP.h_type,2
			mov	esi,edx
			lea	ecx,[edx+16]
			mov	edx,[edx].S_HEAP.h_prev
			free  ( ecx  )
			.if	esi == _heap_base
				mov	_heap_base,edx
				mov	_heap_base[4],edx
			.endif
		.else
			mov	edx,[edx].S_HEAP.h_prev
		.endif
	.endw
	ret
__purgeheap ENDP

	END
