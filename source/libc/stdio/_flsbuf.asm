include stdio.inc
include io.inc
include direct.inc

	.code

	ASSUME	esi: LPFILE

_flsbuf PROC USES esi edi ebx,
	char:	SIZE_T,
	fp:	LPFILE

	mov	esi,fp
	mov	edi,[esi].iob_flag
	test	edi,_IOREAD or _IOWRT or _IORW
	jz	error
	test	edi,_IOSTRG
	jnz	error
	mov	ebx,[esi].iob_file

	.if	edi & _IOREAD

		xor	eax,eax
		mov	[esi].iob_cnt,eax
		test	edi,_IOEOF
		jz	error

		mov	eax,[esi].iob_base
		mov	[esi].iob_ptr,eax
		and	edi,not _IOREAD
	.endif

	or	edi,_IOWRT
	and	edi,not _IOEOF
	mov	[esi].iob_flag,edi
	xor	eax,eax
	mov	[esi].iob_cnt,eax

	.if	!( edi & _IOMYBUF or _IONBF or _IOYOURBUF )
		_isatty( ebx )
		.if	!( ( esi == offset stdout || esi == offset stderr ) && eax )
			_getbuf( esi )
		.endif
	.endif

	mov	eax,[esi].iob_flag
	xor	edi,edi
	mov	[esi].iob_cnt,edi

	.if	eax & _IOMYBUF or _IOYOURBUF

		mov	eax,[esi].iob_base
		mov	edi,[esi].iob_ptr
		sub	edi,eax
		inc	eax
		mov	[esi].iob_ptr,eax
		mov	eax,[esi].iob_bufsize
		dec	eax
		mov	[esi].iob_cnt,eax

		xor	eax,eax

		.if	sdword ptr edi > eax
			_write( ebx, [esi].iob_base, edi )
		.elseif sdword ptr ebx > eax && _osfile[ebx] & FH_APPEND
			SetFilePointer( _osfhnd[ebx*4], eax, eax, SEEK_END )
			xor	eax,eax
		.endif
		mov	edx,char
		mov	ebx,[esi].iob_base
		mov	[ebx],dl
	.else
		inc	edi
		_write( ebx, addr char, edi )
	.endif
	cmp	eax,edi
	jne	error
	movzx	eax,byte ptr char
toend:
	ret
error:
	or	edi,_IOERR
	mov	[esi].iob_flag,edi
	mov	eax,-1
	jmp	toend
_flsbuf ENDP

	END
