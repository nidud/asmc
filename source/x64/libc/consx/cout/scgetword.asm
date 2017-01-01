include consx.inc

	.data
;
; These are characters used as valid identifiers
;
idchars db '0123456789_?@abcdefghijklmnopqrstuvwxyz',0

	.code

	OPTION	WIN64:3, STACKBASE:rsp

scgetword PROC USES rsi rdi rbx rbp linebuf:LPSTR
	mov	rsi,rcx
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
	;mov	esi,linebuf
	mov	ecx,32
	xor	eax,eax
@@:
	getxyc( edi, ebx )
	inc	edi
	call	idtestal
	jz	@F
	mov	[rsi],al
	inc	rsi
	dec	ecx
	jnz	@B
@@:
	mov	BYTE PTR [rsi],0
	mov	rdx,linebuf
	sub	eax,eax
	cmp	al,[rdx]
	je	@F
	mov	rax,rdx
@@:
	ret
idtestal:
	push	rdi
	push	rcx
	push	rax
	cmp	al,'A'
	jb	@F
	cmp	al,'Z'
	ja	@F
	or	al,20h
@@:
	lea	rdi,idchars
	mov	rcx,sizeof(idchars)
	repne	scasb
	cmp	BYTE PTR [rdi-1],0
	pop	rax
	pop	rcx
	pop	rdi
	retn
scgetword ENDP

	END
