include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp
	ASSUME	rbx: LPFILE

fwrite PROC USES rsi rdi rbx r12 r13 r14,
	buf:	LPSTR,
	rsize:	SINT,
	num:	SINT,
	fp:	LPFILE

	mov	rsi,rcx ; buf
	mov	rbx,r9	; fp
	mov	eax,edx ; rsize
	mul	r8d	; num
	mov	edi,eax
	mov	r12d,eax

	mov	r13d,_MAXIOBUF
	.if	[rbx].iob_flag & _IOMYBUF or _IONBF or _IOYOURBUF
		mov r13d,[rbx].iob_bufsize
	.endif

	.while	edi
		mov	r8d,[rbx].iob_cnt
		.if	[rbx].iob_flag & _IOMYBUF or _IOYOURBUF && r8d

			.if	edi < r8d
				mov r8d,edi
			.endif

			memcpy( [rbx].iob_ptr, rsi, r8 )
			sub	edi,r8d
			sub	[rbx].iob_cnt,r8d
			add	[rbx].iob_ptr,r8
			add	rsi,r8

		.elseif edi >= r13d

			.if	[rbx].iob_flag & _IOMYBUF or _IOYOURBUF
				fflush( rbx )
				test	rax,rax
				jnz	break
			.endif

			mov	eax,edi
			mov	ecx,r13d

			.if	ecx
				xor	edx,edx
				div	ecx
				mov	eax,edi
				sub	eax,edx
			.endif
			mov	r14d,eax

			_write( [rbx].iob_file, rsi, rax )
			cmp	rax,-1
			je	error

			sub	rdi,rax
			add	rsi,rax
			cmp	eax,r14d
			jb	error
		.else
			movzx	rax,BYTE PTR [rsi]
			_flsbuf( rax, rbx )
			cmp	rax,-1
			je	break
			inc	rsi
			dec	rdi
			mov	eax,[rbx].iob_bufsize
			.if	!eax
				mov eax,1
			.endif
			mov	r13,rax
		.endif
	.endw
	mov	eax,num
toend:
	ret
error:
	or	[rbx].iob_flag,_IOERR
break:
	mov	rax,r12
	sub	rax,rdi
	xor	rdx,rdx
	div	rsize
	jmp	toend
fwrite	ENDP

	END
