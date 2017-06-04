include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

_stricmp PROC dst:LPSTR, src:LPSTR
	push	esi
	push	edi
	push	ecx
	mov	edi,12[esp+4]
	mov	esi,12[esp+8]
	mov	eax,-1
	ALIGN	16
lupe:
	test	al,al
	jz	toend
	mov	al,[esi]
	cmp	al,[edi]
	lea	esi,[esi+1]
	lea	edi,[edi+1]
	je	lupe
	mov	ah,[edi-1]
	sub	ax,'AA'
	cmp	al,'Z'-'A'+1
	sbb	cl,cl
	and	cl,'a'-'A'
	cmp	ah,'Z'-'A'+1
	sbb	ch,ch
	and	ch,'a'-'A'
	add	ax,cx
	add	ax,'AA'
	cmp	ah,al
	je	lupe
	sbb	al,al
	sbb	al,-1
toend:
	movsx	eax,al
	pop	ecx
	pop	edi
	pop	esi
	ret
_stricmp ENDP

	END
