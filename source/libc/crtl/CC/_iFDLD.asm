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
	sar	ecx,20
	and	cx,0x07FF
	jz	L004
	cmp	cx,0x07FF
	je	@F
	add	cx,0x3C00
	jmp	L003
@@:
	or	ch,0x7F
	test	edx,0x7FFFFFFF
	jnz	@F
	test	eax,eax
	jz	L003
@@:
;	int	3	  ; Invalid exception
	or	edx,0x40000000
L003:
	or	edx,0x80000000
	jmp	toend
L004:
	test	edx,edx
	jnz	@F
	test	eax,eax
	jz	toend
@@:
	or	cx,0x3C01
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
	shl	ecx,1
	rcr	cx,1
	mov	[ebx+8],cx
	ret
_iFDLD	endp

	END
