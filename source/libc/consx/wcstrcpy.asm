include consx.inc
include string.inc

	.code

wcstrcpy PROC USES esi edi ebx cp:LPSTR, wc:PVOID, count
	mov	edi,cp
	mov	esi,wc
	mov	ecx,count
	mov	bl,[esi+1]
	and	bl,0Fh
@@:
	test	ecx,ecx
	jz	toend
	dec	ecx
	lodsw
	cmp	al,' '
	jbe	@B
	cmp	al,176
	ja	@B
	sub	esi,2
	test	ecx,ecx
	jz	toend
lup:
	lodsw
	cmp	al,176
	ja	toend
	and	ah,0Fh
	cmp	ah,bl;13
	je	@F
	mov	ah,al
	mov	al,'&'
	stosb
	mov	al,ah
@@:
	stosb
	dec	ecx
	jnz	lup
toend:
	mov	BYTE PTR [edi],0
	strtrim( cp )
	ret
wcstrcpy ENDP

	END
