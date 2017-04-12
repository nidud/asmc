include stdio.inc
include io.inc
include errno.inc
include winbase.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	rbx: PTR _iobuf

ftell	PROC USES rsi rdi rbx r12 r13 r14 r15,
	fp:	LPFILE

	mov	rbx,rcx
	xor	eax,eax
	.if	SDWORD PTR [rbx]._cnt < eax
		mov	[rbx]._cnt,eax
	.endif

	mov	eax,[rbx]._file
	lea	r14,_osfhnd
	mov	r14,[r14+rax*8]
	lea	r15,_osfile
	mov	r15b,[r15+rax]

	.if	SetFilePointer( r14, 0, 0, SEEK_CUR ) == -1
		call	osmaperr
		jmp	toend
	.endif
	mov	r13,rax

	.if	SQWORD PTR rax < 0
		mov	rax,-1
		jmp	toend
	.endif

	mov	ecx,[rbx]._flag
	.if	!(ecx & ( _IOMYBUF or _IOYOURBUF ) )

		sub	eax,[rbx]._cnt
		jmp	toend
	.endif
	mov	rdi,[rbx]._ptr
	sub	rdi,[rbx]._base

	.if	ecx & _IOWRT or _IOREAD

		.if	r15b & FH_TEXT

			mov	rax,[rbx]._base
			.while	rax < [rbx]._ptr
				.if	BYTE PTR [rax] == 10
					inc	rdi
				.endif
				inc	rax
			.endw
		.endif

	.elseif !(ecx & _IORW)
		mov	errno,EINVAL
		mov	eax,-1
		jmp	toend
	.endif
	mov	rax,rdi
	cmp	r13,0
	je	toend

	.if	ecx & _IOREAD

		mov	eax,[rbx]._cnt
		.if	!eax
			mov rdi,rax
		.else
			add	rax,[rbx]._ptr
			sub	rax,[rbx]._base
			mov	r12,rax

			.if	r15b & FH_TEXT

				.if	SetFilePointer( r14, 0, 0, SEEK_END ) == r13

					mov	rax,[rbx]._base
					mov	rcx,rax
					add	rax,r12
					.while	rcx < rax
						.if BYTE PTR [rcx] == 10
							inc r12
						.endif
						inc	rcx
					.endw
					.if	[rbx]._flag & _IOCTRLZ
						inc	r12
					.endif
				.else

					SetFilePointer( r14, r13d, 0, SEEK_SET )
					mov	eax,[ebx]._flag

					.if	r12 <= 512 && ( eax & _IOMYBUF ) && !( eax & _IOSETVBUF )
						mov	r12,512
					.else
						mov	eax,[ebx]._bufsiz
						mov	r12,rax
					.endif
					.if	r15b & FH_CRLF
						inc	r12
					.endif
				.endif
			.endif
			mov	rax,r12
			sub	r13,rax
		.endif
	.endif
	add	rdi,r13
	mov	rax,rdi
toend:
	ret
ftell	ENDP

	END
