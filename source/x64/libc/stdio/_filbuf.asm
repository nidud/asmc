include stdio.inc
include io.inc

	.code

	ASSUME	rsi: LPFILE

_filbuf PROC USES rsi rdi fp:LPFILE

	mov	rsi,rcx
	mov	edi,[rsi]._flag

	mov	rax,-1
	.if	!( edi & _IOREAD or _IOWRT or _IORW ) || edi & _IOSTRG
		jmp	toend
	.endif
	.if	edi & _IOWRT
		or	[rsi]._flag,_IOERR
		jmp	toend
	.endif

	or	edi,_IOREAD
	mov	[rsi]._flag,edi
	.if	!( edi & _IOMYBUF or _IONBF or _IOYOURBUF )
		_getbuf( rsi )
		mov	edi,[rsi]._flag
	.else
		mov	rax,[rsi]._base
		mov	[rsi]._ptr,rax
	.endif

	_read ( [rsi]._file, [rsi]._base, [rsi]._bufsiz )
	mov	[rsi]._cnt,eax

	.if	sdword ptr eax < 2
		.if	eax
			mov	eax,_IOERR
		.else
			mov	eax,_IOEOF
		.endif
		or	[rsi]._flag,eax
		xor	eax,eax
		mov	[rsi]._cnt,eax
		dec	rax
		jmp	toend
	.endif

	.if	!( edi & _IOWRT or _IORW )
		lea	rax,_osfile
		add	eax,[rsi]._file
		mov	al,[rax]
		and	al,FH_TEXT or FH_EOF
		.if	al == FH_TEXT or FH_EOF
			or [rsi]._flag,_IOCTRLZ
		.endif
	.endif

	mov	eax,[rsi]._bufsiz
	.if	eax == _MINIOBUF && edi & _IOMYBUF && !( edi & _IOSETVBUF )
		mov	[rsi]._bufsiz,_INTIOBUF
	.endif

	dec	[rsi]._cnt
	inc	[rsi]._ptr
	mov	rsi,[rsi]._ptr
	dec	rsi
	movzx	rax,byte ptr [rsi]
toend:
	ret
_filbuf ENDP

	END
