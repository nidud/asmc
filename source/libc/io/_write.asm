include io.inc
include errno.inc

	.code

_write	PROC USES edi esi ebx h:SINT, b:PVOID, l:SIZE_T
  local result, count, lb[1026]:byte
	mov	eax,l
	mov	ebx,h
	test	eax,eax
	jz	toend
	.if	ebx >= _NFILE_
		xor	eax,eax
		mov	oserrno,eax
		mov	errno,EBADF
		dec	eax
		jmp	toend
	.endif
	.if	_osfile[ebx] & FH_APPEND
		_lseek( h, 0, SEEK_END )
	.endif
	xor	eax,eax
	mov	result,eax
	mov	count,eax
	.if	_osfile[ebx] & FH_TEXT
		mov	esi,b
		.repeat
			mov	eax,esi
			sub	eax,b
			.break .if eax >= l
			lea	edi,lb
			.repeat
				lea	edx,lb
				mov	eax,edi
				sub	eax,edx
				.break .if eax >= 1024
				mov	eax,esi
				sub	eax,b
				.break .if eax >= l
				mov	al,[esi]
				.if	al == 10
					mov byte ptr [edi],13
					inc edi
				.endif
				mov	[edi],al
				inc	esi
				inc	edi
				inc	count
			.until	0
			lea	eax,lb
			mov	edx,edi
			sub	edx,eax
			.if	!oswrite( h, addr lb, edx )
				inc	result
				.break
			.endif
			lea	ecx,lb
			mov	edx,edi
			sub	edx,ecx
		.until	eax < edx
	.else
		.if	oswrite( h, b, l )
			jmp	toend
		.endif
		inc	result
	.endif

	mov	eax,count
	.if	!eax
		.if	eax == result
			.if	oserrno == 5 ; access denied
				mov errno,EBADF
			.endif
		.else
			.if	_osfile[ebx] & FH_DEVICE
				mov	ebx,b
				cmp	byte ptr [ebx],26
				je	toend
			.endif
			mov	errno,ENOSPC
			mov	oserrno,0
		.endif
		dec	eax
	.endif
toend:
	ret
_write	ENDP

	END
