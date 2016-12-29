include iost.inc
include io.inc
include string.inc

PUBLIC	oupdate
PUBLIC	odecrypt

	.data
	oupdate	 dd 0
	odecrypt dd 0

	.code

	ASSUME ebx:ptr S_IOST

ioread	PROC USES esi edi ebx edx iost:PTR S_IOST
	mov	ebx,iost
	sub	eax,eax
	mov	esi,[ebx].ios_flag
	test	esi,IO_MEMBUF
	jnz	toend
	mov	edi,[ebx].ios_c
	sub	edi,[ebx].ios_i
	jnz	copy
do:
	mov	[ebx].ios_i,eax
	mov	[ebx].ios_c,edi
	mov	ecx,[ebx].ios_size
	sub	ecx,edi
	mov	eax,[ebx].ios_bp
	add	eax,edi
	osread( [ebx].ios_file, eax, ecx )
	add	[ebx].ios_c,eax
	add	eax,edi
	jz	toend
	and	esi,IO_UPDTOTAL or IO_USECRC or IO_USEUPD or IO_CRYPT
	jnz	crypt
toend:
	test	eax,eax
	ret
crypt:
	test	esi,IO_CRYPT
	jz	@F
	call	odecrypt
@@:
	test	esi,IO_UPDTOTAL
	jz	@F
	add	dword ptr [ebx].S_IOST.ios_total,eax
	adc	dword ptr [ebx].S_IOST.ios_total[4],0
@@:
	test	esi,IO_USECRC
	jz	@F
	mov	edx,edi
	mov	esi,ebx
	call	oupdcrc
	mov	esi,[ebx].ios_flag
@@:
	test	esi,IO_USEUPD
	jz	toend
	push	eax
	push	0
	call	oupdate
	dec	eax
	pop	eax
	jnz	error
	jmp	toend
copy:
	cmp	edi,[ebx].ios_c
	je	eof$
	mov	eax,[ebx].ios_bp
	add	eax,[ebx].ios_i
	memcpy( [ebx].ios_bp, eax, edi )
	xor	eax,eax
	jmp	do
error:
	call	osmaperr
	or	[ebx].ios_flag,IO_ERROR
eof$:
	xor	eax,eax
	jmp	toend
ioread	ENDP

	END
