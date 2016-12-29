include iost.inc
include io.inc
include stdio.inc
include string.inc
include alloc.inc

	.code

ogetl	PROC filename:LPSTR, buffer:LPSTR, bsize
	memset( addr STDI, 0, sizeof(S_IOST) )
	osopen( filename, _A_NORMAL, M_RDONLY, A_OPEN )
	mov	STDI.ios_file,eax
	inc	eax
	jz	toend
	malloc( OO_MEM64K )
	jz	error
	mov	STDI.ios_bp,eax
	mov	STDI.ios_size,OO_MEM64K
	mov	eax,bsize
	mov	STDI.ios_line,eax
	mov	eax,buffer
	mov	STDI.ios_crc,eax
toend:
	ret
error:
	_close( STDI.ios_file )
	xor	eax,eax
	jmp	toend
ogetl	ENDP

ogets	PROC USES edi
	mov	edi,STDI.ios_crc
	mov	ecx,STDI.ios_line
	sub	ecx,2
	call	ogetc
	jz	toend
@@:
	cmp	al,0Dh
	je	@0Dh
	cmp	al,0Ah
	je	@F
	test	al,al
	jz	toend
	mov	[edi],al
	inc	edi
	dec	ecx
	jz	@F
	call	ogetc
	jnz	@B
@@:
	inc	al
	jmp	toend
@0Dh:
	call	ogetc
toend:
	mov	eax,0
	mov	[edi],al
	jz	@F
	mov	eax,STDI.ios_crc
	mov	ecx,edi
	sub	ecx,eax
	test	edi,edi
@@:
	ret
ogets	ENDP

	END
