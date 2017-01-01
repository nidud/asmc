include alloc.inc

EXTRN	memseg:QWORD

M_BLOCK STRUC	; Memory Block Header
m_size	dq ?
m_used	dq ?
m_prev	dq ?
m_next	dq ?
M_BLOCK ENDS

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

__purgeheap PROC
	mov	rdx,memseg
	.while	rdx
		.while	[rdx].M_BLOCK.m_size
			.if	[rdx].M_BLOCK.m_used == 0
				mov	rcx,[rdx].M_BLOCK.m_size
				.while	[rdx+rcx].M_BLOCK.m_used == 0
					add rcx,[rdx+rcx].M_BLOCK.m_size
					mov [rdx].M_BLOCK.m_size,rcx
				.endw
			.endif
			add	rdx,[rdx].M_BLOCK.m_size
		.endw
		mov	rdx,[rdx].M_BLOCK.m_prev
		mov	rdx,[rdx].M_BLOCK.m_prev
	.endw
	mov	rdx,memseg
	.while	rdx
		mov	rcx,[rdx].M_BLOCK.m_size
		.if	![rcx+rdx].M_BLOCK.m_size && ![rdx].M_BLOCK.m_used
			mov	[rdx].M_BLOCK.m_used,2
			mov	rax,rdx
			lea	rcx,[rdx+sizeof(M_BLOCK)]
			mov	rdx,[rdx].M_BLOCK.m_prev
			free  ( rcx  )
			.if	rax == memseg
				mov	memseg,rdx
				mov	memseg[8],rdx
			.endif
		.else
			mov	rdx,[rdx].M_BLOCK.m_prev
		.endif
	.endw
	ret
__purgeheap ENDP

	END
