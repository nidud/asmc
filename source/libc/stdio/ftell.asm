include stdio.inc
include io.inc
include errno.inc

	.code

	ASSUME	ebx: PTR S_FILE

ftell	PROC USES esi edi ebx,
	fp:	LPFILE
local	rdcnt:	SIZE_T,
	filepos:SIZE_T

	mov	ebx,fp
	xor	eax,eax
	.if	SDWORD PTR [ebx].iob_cnt < eax
		mov	[ebx].iob_cnt,eax
	.endif

	mov	eax,[ebx].iob_file
	mov	eax,_osfhnd[eax*4]
	.if	SetFilePointer( eax, 0, 0, SEEK_CUR ) == -1
		call	osmaperr
		jmp	toend
	.endif
	mov	filepos,eax

	.if	SDWORD PTR eax < 0
		mov	eax,-1
		jmp	toend
	.endif

	mov	ecx,[ebx].iob_flag
	.if	!(ecx & ( _IOMYBUF or _IOYOURBUF ) )
		sub	eax,[ebx].iob_cnt
		jmp	toend
	.endif
	mov	edi,[ebx].iob_ptr
	sub	edi,[ebx].iob_base

	.if	ecx & _IOWRT or _IOREAD
		mov	eax,[ebx].iob_file
		.if	_osfile[eax] & FH_TEXT
			mov	eax,[ebx].iob_base
			.while	eax < [ebx].iob_ptr
				.if	BYTE PTR [eax] == 10
					inc	edi
				.endif
				inc	eax
			.endw
		.endif
	.elseif !(ecx & _IORW)
		mov	errno,EINVAL
		mov	eax,-1
		jmp	toend
	.endif
	mov	eax,edi
	cmp	filepos,0
	je	toend

	.if	ecx & _IOREAD

		mov	eax,[ebx].iob_cnt
		.if	!eax
			mov edi,eax
		.else
			add	eax,[ebx].iob_ptr
			sub	eax,[ebx].iob_base
			mov	rdcnt,eax
			mov	eax,[ebx].iob_file

			.if	_osfile[eax] & FH_TEXT
				mov	ecx,_osfhnd[eax*4]
				.if	SetFilePointer( ecx, 0, 0, SEEK_END ) == filepos
					mov	eax,[ebx].iob_base
					mov	ecx,eax
					add	eax,rdcnt
					.while	ecx < eax
						.if BYTE PTR [ecx] == 10
							inc rdcnt
						.endif
						inc	ecx
					.endw
					.if	[ebx].iob_flag & _IOCTRLZ
						inc	rdcnt
					.endif
				.else
					mov	eax,[ebx].iob_file
					mov	ecx,_osfhnd[eax*4]
					SetFilePointer( ecx, filepos, 0, SEEK_SET )
					mov	eax,[ebx].iob_flag

					.if	rdcnt <= 512 && ( eax & _IOMYBUF ) && !( eax & _IOSETVBUF )
						mov	rdcnt,512
					.else
						mov	eax,[ebx].iob_bufsize
						mov	rdcnt,eax
					.endif
					mov	eax,[ebx].iob_file

					.if	_osfile[eax] & FH_CRLF
						inc	rdcnt
					.endif
				.endif
			.endif
			mov	eax,rdcnt
			sub	filepos,eax
		.endif
	.endif
	add	edi,filepos
	mov	eax,edi
toend:
	ret
ftell	ENDP

	END
