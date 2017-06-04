include iost.inc
include io.inc

	.code

oungetc PROC
	mov	eax,STDI.ios_i
	test	eax,eax
	jz	@F
	dec	STDI.ios_i
	add	eax,STDI.ios_bp
	movzx	eax,byte ptr [eax-1]
	ret
     @@:
	test	STDI.ios_flag,IO_MEMBUF
	jz	@F
	dec	eax
	ret
     @@:
	_lseeki64( STDI.ios_file, 0, SEEK_CUR )
	cmp	edx,-1
	jne	@F
	cmp	eax,-1
	jne	@F
	ret
     @@:
	mov	ecx,STDI.ios_c	; last read size to CX
	cmp	ecx,eax
	ja	oungetc_error	; stream not align if above
	je	oungetc_eof	; EOF == top of file
	cmp	eax,STDI.ios_size
	jne	@F
	cmp	dword ptr STDI.ios_offset,0
	je	oungetc_eof
     @@:
	sub	eax,ecx		; adjust offset to start
	mov	ecx,STDI.ios_size
	cmp	ecx,eax
	jae	oungetc_07
	sub	eax,ecx
   oungetc_06:
	push	ecx
	oseek ( eax, SEEK_SET )
	pop	eax
	jz	oungetc_eof
	cmp	eax,STDI.ios_c
	ja	oungetc_error
	mov	STDI.ios_c,eax
	mov	STDI.ios_i,eax
	jmp	oungetc
    oungetc_07:
	mov	ecx,eax
	xor	eax,eax
	jmp	oungetc_06
    oungetc_error:
	or	STDI.ios_flag,IO_ERROR
    oungetc_eof:
	mov	eax,-1
	ret
oungetc ENDP

	END
