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
	.if	[rbx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF
		mov r13d,[rbx]._bufsiz
	.endif

	.while	edi
		mov	r8d,[rbx]._cnt
		.if	[rbx]._flag & _IOMYBUF or _IOYOURBUF && r8d

			.if	edi < r8d
				mov r8d,edi
			.endif

			memcpy( [rbx]._ptr, rsi, r8 )
			sub	edi,r8d
			sub	[rbx]._cnt,r8d
			add	[rbx]._ptr,r8
			add	rsi,r8

		.elseif edi >= r13d

			.if	[rbx]._flag & _IOMYBUF or _IOYOURBUF
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

			_write( [rbx]._file, rsi, rax )
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
			mov	eax,[rbx]._bufsiz
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
	or	[rbx]._flag,_IOERR
break:
	mov	rax,r12
	sub	rax,rdi
	xor	rdx,rdx
	div	rsize
	jmp	toend
fwrite	ENDP

	END
