include stdio.inc
include io.inc
include errno.inc
include string.inc

	.code

	ASSUME	rbx: ptr _iobuf
	OPTION	WIN64:2, STACKBASE:rsp

fread PROC USES rsi rdi rbx r12 r13 r14 r15,
	buf:	LPSTR,
	rsize:	SINT,
	num:	SINT,
	fp:	LPFILE

	mov	rsi,rcx		; buf
	mov	r14d,edx	; rsize
	mov	r15d,r8d	; num
	mov	rbx,r9		; fp
	mov	eax,edx
	mul	r8d
	mov	r12d,eax
	mov	edi,eax
	test	eax,eax
	jz	toend
	mov	edx,_MAXIOBUF

	.if	[rbx]._flag & _IOMYBUF or _IONBF or _IOYOURBUF
		mov	edx,[rbx]._bufsiz
	.endif
	mov	r13d,edx

	.while	edi
		mov	r8d,[rbx]._cnt
		.if	[rbx]._flag & _IOMYBUF or _IOYOURBUF && r8d
			.if	edi < r8d
				mov	r8d,edi
			.endif
			memcpy( rsi, [rbx]._ptr, r8 )
			sub	edi,r8d
			sub	[rbx]._cnt,r8d
			add	[rbx]._ptr,r8
			add	rsi,r8
		.elseif edi >= r13d
			mov	eax,edi
			mov	ecx,r13d
			.if	ecx
				xor	edx,edx
				div	ecx
				mov	eax,edi
				sub	eax,edx
			.endif

			.if	!_read( [rbx]._file, rsi, rax )
				jmp	error
			.elseif eax == -1
				jmp	error
			.endif
			sub	edi,eax
			add	rsi,rax
		.else
			.if	_filbuf( rbx ) == -1
				jmp	break
			.endif
			mov	[rsi],al
			inc	rsi
			dec	edi
			mov	eax,[rbx]._bufsiz
			mov	r13d,eax
		.endif
	.endw
	mov	rax,r15
toend:
	ret
error:
	or	[rbx]._flag,_IOEOF
break:
	mov	eax,r12d
	sub	eax,edi
	xor	edx,edx
	div	r14d
	jmp	toend
fread	ENDP

	END
