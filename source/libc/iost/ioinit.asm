include iost.inc
include io.inc
include alloc.inc
include stdio.inc
include string.inc

	.code

ioinit	PROC USES edi io:PTR S_IOST, bsize

	mov edi,io
	mov edx,[edi].S_IOST.ios_file
	mov ecx,SIZE S_IOST
	xor eax,eax
	rep stosb
	mov edi,io

	mov [edi].S_IOST.ios_file,edx
	dec [edi].S_IOST.ios_crc	; CRC to FFFFFFFFh
	mov eax,bsize

	.if eax == OO_MEM64K

		mov [edi].S_IOST.ios_size,eax
		_aligned_malloc( _SEGSIZE_, _SEGSIZE_ )
	.else
		.if !eax

			mov eax,OO_MEM64K
		.endif
		mov [edi].S_IOST.ios_size,eax

		.if malloc( eax ) && !bsize

			mov [edi].S_IOST.ios_bp,eax
			ioread( edi )
			_filelength( [edi].S_IOST.ios_file )
			mov dword ptr [edi].S_IOST.ios_fsize,eax
			mov dword ptr [edi].S_IOST.ios_fsize[4],edx

			.if !edx && eax <= STDI.ios_c

				or [edi].S_IOST.ios_flag,IO_MEMBUF
			.endif
			mov eax,[edi].S_IOST.ios_bp
		.endif
	.endif

	mov [edi].S_IOST.ios_bp,eax
	test eax,eax
	ret

ioinit	ENDP

	END
