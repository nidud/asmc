include stdio.inc
include io.inc
include malloc.inc
include crtl.inc

extrn	_stdbuf:qword

	.code

	OPTION	WIN64:2, STACKBASE:rsp

_stbuf	PROC USES rbx fp:LPFILE
	mov rbx,rcx
	assume rbx:ptr _iobuf

	.if _isatty( [rbx]._file )

		xor rax,rax
		xor rdx,rdx
		lea r10,stdout
		lea r11,stderr

		.if rbx != r10
			.if rbx != r11
			    jmp @F
			.endif
			inc rdx
		.endif
		mov ecx,[rbx]._flag
		and ecx,_IOMYBUF or _IONBF or _IOYOURBUF
		jnz @F
		or  ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
		mov [rbx]._flag,ecx
		shl rdx,3
		lea r10,_stdbuf
		add rdx,r10
		mov rax,[rdx]
		mov ecx,_INTIOBUF
		.if !eax
			push rdx
			malloc(rcx)
			pop rdx
			mov [rdx],rax
			mov ecx,_INTIOBUF
			.if ZERO?
			    lea rax,[rbx]._charbuf
			    mov ecx,4
			.endif
		.endif
		mov [rbx]._ptr,rax
		mov [rbx]._base,rax
		mov [rbx]._bufsiz,ecx
		mov rax,1
	.endif
@@:
	ret
_stbuf	ENDP

	END
