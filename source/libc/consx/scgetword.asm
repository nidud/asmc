include consx.inc

	.data
;
; These are characters used as valid identifiers
;
idchars db '0123456789_?@abcdefghijklmnopqrstuvwxyz',0

	.code

scgetword PROC USES esi edi ebx linebuf:LPSTR
	call	_wherex		; get cursor x,y pos
	mov	edi,eax
	mov	ebx,edx
	inc	edi		; to start of line..
@@:
	dec	edi		; moving left seeking a valid character
	jz	@F
	getxyc( edi, ebx )
	call	idtestal
	jz	@B
	mov	eax,edi
	dec	eax
	getxyc( eax, ebx )
	call	idtestal
	jnz	@B
@@:
	mov	esi,linebuf
	mov	ecx,32
	xor	eax,eax
@@:
	getxyc( edi, ebx )
	inc	edi
	call	idtestal
	jz	@F
	mov	[esi],al
	inc	esi
	dec	ecx
	jnz	@B
@@:
	mov	BYTE PTR [esi],0
	mov	edx,linebuf
	sub	eax,eax
	cmp	al,[edx]
	je	@F
	mov	eax,edx
@@:
	ret
idtestal:
	push	edi
	push	ecx
	push	eax
	cmp	al,'A'
	jb	@F
	cmp	al,'Z'
	ja	@F
	or	al,20h
@@:
	mov	edi,offset idchars
	mov	ecx,sizeof idchars
	repne	scasb
	cmp	BYTE PTR [edi-1],0
	pop	eax
	pop	ecx
	pop	edi
	retn
scgetword ENDP

	END
