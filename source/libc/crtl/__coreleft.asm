include alloc.inc

	.code

__coreleft PROC USES ebx

	xor	eax,eax		; EAX: free memory
	mov	ecx,_heap_base	; ECX: total allocated

	.if	ecx

		mov	edx,ecx
		mov	ecx,[edx].S_HEAP.h_next
		.while	ecx

			add eax,[ecx]
			mov ecx,[ecx].S_HEAP.h_next
		.endw

		mov	ecx,eax
		xor	eax,eax
		.while	edx

			mov	ebx,[edx]
			.while	ebx

				add	ecx,ebx
				.if	[edx].S_HEAP.h_type == 0

					add	eax,ebx
				.endif
				add	edx,ebx
				mov	ebx,[edx]
			.endw
			mov	edx,[edx].S_HEAP.h_prev
			mov	edx,[edx].S_HEAP.h_prev
		.endw
	.endif
	ret

__coreleft ENDP

	END
