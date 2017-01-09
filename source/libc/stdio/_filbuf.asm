include stdio.inc
include io.inc

	.code

	ASSUME	ESI: LPFILE

_filbuf PROC USES esi edi,
	fp:	LPFILE

	mov	esi,fp
	mov	edi,[esi].iob_flag

	mov	eax,-1
	.if	!( edi & _IOREAD or _IOWRT or _IORW ) || edi & _IOSTRG
		jmp	toend
	.endif
	.if	edi & _IOWRT
		or	[esi].iob_flag,_IOERR
		jmp	toend
	.endif

	or	edi,_IOREAD
	mov	[esi].iob_flag,edi
	.if	!( edi & _IOMYBUF or _IONBF or _IOYOURBUF )
		_getbuf( fp )
		mov	edi,[esi].iob_flag
	.else
		mov	eax,[esi].iob_base
		mov	[esi].iob_ptr,eax
	.endif

	_read ( [esi].iob_file, [esi].iob_base, [esi].iob_bufsize )
	mov	[esi].iob_cnt,eax

	.if	sdword ptr eax < 2
		.if	eax
			mov	eax,_IOERR
		.else
			mov	eax,_IOEOF
		.endif
		or	[esi].iob_flag,eax
		xor	eax,eax
		mov	[esi].iob_cnt,eax
		dec	eax
		jmp	toend
	.endif

	.if	!( edi & _IOWRT or _IORW )
		lea	eax,_osfile
		add	eax,[esi].iob_file
		mov	al,[eax]
		and	al,FH_TEXT or FH_EOF
		.if	al == FH_TEXT or FH_EOF
			or [esi].iob_flag,_IOCTRLZ
		.endif
	.endif

	mov	eax,[esi].iob_bufsize
	.if	eax == _MINIOBUF && edi & _IOMYBUF && !( edi & _IOSETVBUF )
		mov	[esi].iob_bufsize,_INTIOBUF
	.endif

	dec	[esi].iob_cnt
	inc	[esi].iob_ptr
	mov	esi,[esi].iob_ptr
	dec	esi
	movzx	eax,byte ptr [esi]
toend:
	ret
_filbuf ENDP

	END
