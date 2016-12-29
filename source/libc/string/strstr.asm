include string.inc

	.code

ifndef __SSE__

strstr	PROC USES esi edi ebx edx dst:LPSTR, src:LPSTR
	mov	edi,dst
	mov	esi,src
	strlen( esi )
	jz	nomatch
	mov	ebx,eax
	strlen( edi )
	jz	nomatch
	mov	ecx,eax
	dec	ebx
scan:
	mov	al,[esi]
	repne	scasb
	jne	nomatch
	test	ebx,ebx
	jz	match
	cmp	ecx,ebx
	jb	nomatch
	mov	edx,ebx
compare:
	mov	al,[esi+edx]
	cmp	al,[edi+edx-1]
	jne	scan
	dec	edx
	jnz	compare
match:
	mov	eax,edi
	dec	eax
	jmp	toend
nomatch:
	xor	eax,eax
toend:
	ret
strstr	ENDP

else	; SSE2 - Auto install

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strstr	PROC dst:LPSTR, src:LPSTR

	push	esi
	push	edi
	push	ebp
	push	ebx
	push	edx

	mov	edi,20[esp+4]	; dst
	mov	esi,20[esp+8]	; src

	strlen( esi )
	jz	nomatch
	mov	ebx,eax

	strlen( edi )
	jz	nomatch
	mov	ebp,eax

	dec	ebx
	inc	esi

mainloop:

	movzx	eax,BYTE PTR [esi-1]
	strchr( edi, eax )
	jz	nomatch

	sub	eax,edi
	sub	ebp,eax
	cmp	ebx,ebp
	ja	nomatch

	lea	edi,[edi+eax+1]
	test	ebx,ebx
	jz	match

	mov	eax,edi
	mov	edx,esi
	mov	ecx,ebx
	repe	cmpsb
	mov	edi,eax
	mov	esi,edx
	jnz	mainloop

match:
	mov	eax,edi
	dec	eax
	jmp	toend

nomatch:
	xor	eax,eax

toend:
	pop	edx
	pop	ebx
	pop	ebp
	pop	edi
	pop	esi
	ret	8
strstr	ENDP

endif
	END
