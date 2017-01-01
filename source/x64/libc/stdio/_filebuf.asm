include stdio.inc
include io.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp
	ASSUME	RSI: LPFILE

_filbuf PROC USES rsi rdi fp:LPFILE

	mov	rsi,rcx
	mov	edi,[rsi].iob_flag

	mov	rax,-1
	.if	!( edi & _IOREAD or _IOWRT or _IORW ) || edi & _IOSTRG
		jmp	toend
	.endif
	.if	edi & _IOWRT
		or	[rsi].iob_flag,_IOERR
		jmp	toend
	.endif

	or	edi,_IOREAD
	mov	[rsi].iob_flag,edi
	.if	!( edi & _IOMYBUF or _IONBF or _IOYOURBUF )
		_getbuf( rsi )
		mov	edi,[rsi].iob_flag
	.else
		mov	rax,[rsi].iob_base
		mov	[rsi].iob_ptr,rax
	.endif

	_read ( [rsi].iob_file, [rsi].iob_base, [rsi].iob_bufsize )
	mov	[rsi].iob_cnt,eax

	.if	sdword ptr eax < 2
		.if	eax
			mov	eax,_IOERR
		.else
			mov	eax,_IOEOF
		.endif
		or	[rsi].iob_flag,eax
		xor	eax,eax
		mov	[rsi].iob_cnt,eax
		dec	rax
		jmp	toend
	.endif

	.if	!( edi & _IOWRT or _IORW )
		lea	rax,_osfile
		add	eax,[rsi].iob_file
		mov	al,[rax]
		and	al,FH_TEXT or FH_EOF
		.if	al == FH_TEXT or FH_EOF
			or [rsi].iob_flag,_IOCTRLZ
		.endif
	.endif

	mov	eax,[rsi].iob_bufsize
	.if	eax == _MINIOBUF && edi & _IOMYBUF && !( edi & _IOSETVBUF )
		mov	[rsi].iob_bufsize,_INTIOBUF
	.endif

	dec	[rsi].iob_cnt
	inc	[rsi].iob_ptr
	mov	rsi,[rsi].iob_ptr
	dec	rsi
	movzx	rax,byte ptr [rsi]
toend:
	ret
_filbuf ENDP

	END
