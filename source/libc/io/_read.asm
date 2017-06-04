include io.inc
include errno.inc

ER_ACCESS_DENIED equ 5
ER_BROKEN_PIPE	 equ 109

	.data
	pipech	db _NFILE_ dup(10)
	peekchr db 0

	.code

read	PROC h:SINT, b:PVOID, count:SIZE_T
read	ENDP

_read	PROC USES ebx esi edi h:SINT, b:PVOID, count:SIZE_T
	xor	esi,esi			; nothing read yet
	mov	edi,b
	mov	ebx,h
	xor	eax,eax			; nothing to read or at EOF
	cmp	eax,count
	je	toend
	movzx	ecx,_osfile[ebx]
	test	ecx,FH_EOF
	jnz	toend
	mov	oserrno,eax
	.if	ecx & FH_PIPE or FH_DEVICE
		mov	al,pipech[ebx]
		.if	al != 10
			mov	[edi],al
			mov	pipech[ebx],10
			inc	edi
			inc	esi
			dec	count
		.endif
	.endif
	osread( ebx, edi, count )
	test	ecx,ecx
	jz	error

	add	esi,eax
	mov	edi,b
	mov	al,_osfile[ebx]

	.if	al & FH_TEXT
		and	al,not FH_CRLF
		.if	byte ptr [edi] == 10
			or al,FH_CRLF
		.endif
		mov	_osfile[ebx],al
		mov	edx,edi
		.repeat
			mov	eax,b
			add	eax,esi
			.break .if edi >= eax

			mov	al,[edi]
			.if	al == 26
				.break .if _osfile[ebx] & FH_DEVICE
				or	_osfile[ebx],FH_EOF
				.break
			.endif
			.if	al != 13
				mov	[edx],al
				inc	edi
				inc	edx
				.continue
			.endif
			mov	eax,b
			lea	eax,[eax+esi-1]
			.if	edi < eax
				.if	byte ptr [edi+1] == 10
					add	edi,2
					mov	al,10
				.else
					mov	al,[edi]
					inc	edi
				.endif
				mov	[edx],al
				inc	edx
				.continue
			.endif
			inc	edi
			push	edx
			mov	oserrno,0
			osread( ebx, addr peekchr, 1 )
			pop	edx
			.if	!eax || oserrno
				mov	al,13
			.elseif _osfile[ebx] & FH_DEVICE or FH_PIPE
				mov	al,10
				.if	peekchr != al
					mov	al,peekchr
					mov	pipech[ebx],al
					mov	al,13
				.endif
			.else
				mov	al,10
				.if	b != edx || peekchr != al
					push	edx
					_lseek( ebx, -1, SEEK_CUR )
					pop	edx
					mov	al,13
					.continue .if peekchr == 10
				.endif
			.endif
			mov	[edx],al
			inc	edx
		.until	0
		mov	eax,edx
		sub	eax,b
	.else
		mov	eax,esi
	.endif
toend:
	ret
error:
	xor	eax,eax
	mov	edx,oserrno
	cmp	edx,ER_BROKEN_PIPE
	je	toend
	dec	eax
	cmp	edx,ER_ACCESS_DENIED
	jne	toend
	mov	errno,EBADF
	jmp	toend
_read	ENDP

	END
