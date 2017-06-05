include alloc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

__coreleft PROC USES rbx

	xor rax,rax		; RAX: free memory
	mov rcx,_heap_base	; RCX: total allocated
	.if rcx
		mov rdx,rcx
		mov rcx,[rdx+24]
		.while rcx

			add rax,[rcx]
			mov rcx,[rcx+24]
		.endw
		mov rcx,rax
		xor rax,rax
		.while rdx

			mov rbx,[rdx]
			.while rbx

				add rcx,rbx
				.if BYTE PTR [rdx+8] == 0
					add rax,rbx
				.endif
				add rdx,rbx
				mov rbx,[rdx]
			.endw
			mov rdx,[rdx+16]
			mov rdx,[rdx+16]
		.endw
	.endif
	ret

__coreleft ENDP

	END
