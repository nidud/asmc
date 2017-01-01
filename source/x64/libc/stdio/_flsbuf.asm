include stdio.inc
include io.inc
include direct.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp
	ASSUME	rsi: LPFILE

_flsbuf PROC USES rsi rdi rbx char:SIZE_T, fp:LPFILE

	mov	rsi,rdx
	mov	edi,[rsi].iob_flag
	test	edi,_IOREAD or _IOWRT or _IORW
	jz	error
	test	edi,_IOSTRG
	jnz	error
	mov	ebx,[rsi].iob_file

	.if	edi & _IOREAD

		xor	eax,eax
		mov	[rsi].iob_cnt,eax
		test	edi,_IOEOF
		jz	error

		mov	rax,[rsi].iob_base
		mov	[rsi].iob_ptr,rax
		and	edi,not _IOREAD
	.endif

	or	edi,_IOWRT
	and	edi,not _IOEOF
	mov	[rsi].iob_flag,edi
	xor	eax,eax
	mov	[rsi].iob_cnt,eax

	.if	!( edi & _IOMYBUF or _IONBF or _IOYOURBUF )

		_isatty( ebx )
		lea	r8,stdout
		lea	r9,stderr

		.if	!( ( rsi == r8 || rsi == r9 ) && rax )

			_getbuf( rsi )
		.endif
	.endif

	mov	eax,[rsi].iob_flag
	xor	edi,edi
	mov	[rsi].iob_cnt,edi

	.if	eax & _IOMYBUF or _IOYOURBUF

		mov	rax,[rsi].iob_base
		mov	rdi,[rsi].iob_ptr
		sub	rdi,rax
		inc	rax
		mov	[rsi].iob_ptr,rax
		mov	eax,[rsi].iob_bufsize
		dec	eax
		mov	[rsi].iob_cnt,eax

		xor	eax,eax

		.if	sdword ptr edi > eax

			_write( ebx, [rsi].iob_base, rdi )

		.else
			lea	r8,_osfile
			mov	dl,[r8+rbx]
			.if	sdword ptr ebx > eax && dl & FH_APPEND

				lea	rcx,_osfhnd
				mov	rcx,[rcx+rbx*8]
				SetFilePointer( rcx, eax, rax, SEEK_END )
				xor	eax,eax
			.endif
		.endif

		mov	rdx,char
		mov	rbx,[rsi].iob_base
		mov	[rbx],dl
	.else
		inc	edi
		_write( ebx, addr char, rdi )
	.endif
	cmp	eax,edi
	jne	error
	movzx	eax,byte ptr char
toend:
	ret
error:
	or	edi,_IOERR
	mov	[rsi].iob_flag,edi
	mov	rax,-1
	jmp	toend
_flsbuf ENDP

	END
