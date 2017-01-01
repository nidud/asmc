include stdio.inc
include io.inc
include errno.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	rbx: LPFILE

fseek	PROC USES rsi rdi rbx,
	fp:	LPFILE,
	off:	SIZE_T,
	whence: SIZE_T

	mov	rbx,rcx ; fp
	mov	rsi,rdx ; offset
	mov	rdi,r8	; whence

	.if	r8b != SEEK_SET && r8b != SEEK_CUR && r8b != SEEK_END
		jmp	error
	.endif
	mov	eax,[rbx].iob_flag
	.if	!( eax & _IOREAD or _IOWRT or _IORW )
		jmp	error
	.endif
	and	eax,not _IOEOF
	mov	[rbx].iob_flag,eax

	.if	r8b == SEEK_CUR
		ftell ( rbx )
		add	rsi,rax
		mov	rdi,SEEK_SET
	.endif
	fflush( rbx )

	mov	eax,[rbx].iob_flag
	.if	eax & _IORW
		and	eax,not (_IOWRT or _IOREAD)
		mov	[rbx].iob_flag,eax
	.elseif eax & _IOREAD && eax & _IOMYBUF && !( eax & _IOSETVBUF )
		mov	[rbx].iob_bufsize,_MINIOBUF
	.endif

	mov	eax,[rbx].iob_file
	lea	r8,_osfhnd
	mov	rax,[r8+rax*8]
	.if	SetFilePointer( rax, esi, 0, edi ) == -1
		call	osmaperr
		jmp	toend
	.endif
	xor	rax,rax
toend:
	ret
error:
	mov	errno,EINVAL
	mov	rax,-1
	jmp	toend
fseek	ENDP

	END
