	.486
	.model	flat, c
	.code
	;
	; double[eax] to long double[edx]
	;
_iFDLD	proc uses ecx ebx
	mov	ebx,edx
	mov	edx,[eax+4]
	mov	eax,[eax]
	mov	ecx,edx
	shld	edx,eax,11
	shl	eax,11
	shr	ecx,20
	and	ecx,000007FFh
	jz	L004
	cmp	ecx,000007FFh
	je	@F
	add	ecx,00003C00h
	jmp	L003
@@:
	or	ecx,00007F00h
	test	edx,7FFFFFFFh
	jnz	@F
	test	eax,eax
	jz	L003
@@:
;	int	3	  ; Invalid exception
	or	edx,40000000h
L003:
	or	edx,80000000h
	jmp	toend
L004:
	test	edx,edx
	jnz	@F
	test	eax,eax
	jz	toend
@@:
	or	ecx,00003C01h
	test	edx,edx
	jnz	@F
	xchg	edx,eax
	sub	ecx,32
@@:
	test	edx,edx
	js	toend
	add	eax,eax
	adc	edx,edx
	dec	ecx
	jmp	@B
toend:
	mov	[ebx],eax
	mov	[ebx+4],edx
	add	ecx,ecx
	rcr	cx,1
	mov	[ebx+8],cx
	ret
_iFDLD	endp

	END
