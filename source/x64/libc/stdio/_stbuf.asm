include stdio.inc
include io.inc
include alloc.inc
include crtl.inc

extrn	_stdbuf:qword
extrn	output_flush:qword

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_stbuf	PROC USES rbx fp:LPFILE
	mov	rbx,rcx

	.if	_isatty( [rbx].S_FILE.iob_file )

		xor	rax,rax
		xor	rdx,rdx
		lea	r10,stdout
		lea	r11,stderr

		.if	rbx != r10
			.if	rbx != r11
				jmp	@F
			.endif
			inc	rdx
		.endif
		mov	ecx,[rbx].S_FILE.iob_flag
		and	ecx,_IOMYBUF or _IONBF or _IOYOURBUF
		jnz	@F
		or	ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
		mov	[rbx].S_FILE.iob_flag,ecx
		shl	rdx,3
		lea	r10,_stdbuf
		add	rdx,r10
		mov	rax,[rdx]
		mov	ecx,_INTIOBUF
		.if	!eax
			push	rdx
			malloc( rcx )
			pop	rdx
			mov	[rdx],rax
			mov	ecx,_INTIOBUF
			.if	ZERO?
				lea	rax,[rbx].S_FILE.iob_charbuf
				mov	ecx,4
			.endif
		.endif
		mov	[rbx].S_FILE.iob_ptr,rax
		mov	[rbx].S_FILE.iob_base,rax
		mov	[rbx].S_FILE.iob_bufsize,ecx
		mov	rax,1
	.endif
@@:
	ret
_stbuf	ENDP


__STDIO:
	mov	rax,_flsbuf
	mov	output_flush,rax
	ret

pragma_init __STDIO, 2

	END
