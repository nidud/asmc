include stdio.inc
include malloc.inc
include limits.inc

	.code

	ASSUME	rbx: LPFILE
	OPTION	WIN64:2, STACKBASE:rsp

setvbuf PROC USES rsi rdi rbx r12 r13,
	fp:	LPFILE,
	buf:	LPSTR,
	tp:	SIZE_T,
	bsize:	SIZE_T

	mov	rbx,rcx ; fp
	mov	rdi,rdx ; buf
	mov	r12,r8	; tp
	mov	r13,r9	; bsize

	.if	r12d != _IONBF && (r13 < 2 || r13 > INT_MAX || (r12d != _IOFBF && r12d != _IOLBF))
		mov	rax,-1
		jmp	toend
	.endif

	fflush( rbx )
	_freebuf( rbx )

	mov	esi,[rbx]._flag
	and	esi,not (_IOMYBUF or _IOYOURBUF or _IONBF or _IOSETVBUF or _IOFEOF or _IOFLRTN or _IOCTRLZ)

	.if	r12d & _IONBF
		or	esi,_IONBF
		lea	rdi,[rbx]._charbuf
		mov	r13,4
	.elseif !rdi
		.if	!malloc( r13 )
			mov	rax,-1
			jmp	toend
		.endif
		mov	rdi,rax
		or	esi,_IOMYBUF or _IOSETVBUF
	.else
		or	esi,_IOYOURBUF or _IOSETVBUF
	.endif
	mov	[rbx]._flag,esi
	mov	[rbx]._bufsiz,r13d
	mov	[rbx]._ptr,rdi
	mov	[rbx]._base,rdi
	xor	eax,eax
	mov	[rbx]._cnt,eax
toend:
	ret
setvbuf ENDP

	END
