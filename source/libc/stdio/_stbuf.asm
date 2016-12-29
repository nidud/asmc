include stdio.inc
include io.inc
include alloc.inc
include crtl.inc

extrn	_stdbuf:dword
extrn	output_flush:dword

	.code

_stbuf	PROC USES ebx fp:LPFILE
	mov	ebx,fp
	.if	_isatty( [ebx].S_FILE.iob_file )
		xor	eax,eax
		xor	edx,edx
		.if	ebx != offset stdout
			.if	ebx != offset stderr
				jmp	@F
			.endif
			inc	edx
		.endif
		mov	ecx,[ebx].S_FILE.iob_flag
		and	ecx,_IOMYBUF or _IONBF or _IOYOURBUF
		jnz	@F
		or	ecx,_IOWRT or _IOYOURBUF or _IOFLRTN
		mov	[ebx].S_FILE.iob_flag,ecx
		shl	edx,2
		add	edx,offset _stdbuf
		mov	eax,[edx]
		mov	ecx,_INTIOBUF
		.if	!eax
			push	edx
			malloc( ecx )
			pop	edx
			mov	[edx],eax
			mov	ecx,_INTIOBUF
			.if	ZERO?
				lea	eax,[ebx].S_FILE.iob_charbuf
				mov	ecx,4
			.endif
		.endif
		mov	[ebx].S_FILE.iob_ptr,eax
		mov	[ebx].S_FILE.iob_base,eax
		mov	[ebx].S_FILE.iob_bufsize,ecx
		mov	eax,1
	.endif
@@:
	ret
_stbuf	ENDP


__STDIO:
	mov	eax,_flsbuf
	mov	output_flush,eax
	ret

pragma_init __STDIO, 2

	END
