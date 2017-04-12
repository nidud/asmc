	.486
	.model	flat, c
	.code
	;
	; long [eax] to long double[edx]
	;
_I4LD	proc
	test	eax,eax
	jns	_U4LD
	push	ebx
	mov	ebx,edx
	neg	eax
	mov	edx,0000BFFFh
	jmp	L4TOLD
_I4LD	endp
	;
	; DWORD [eax] to long double[edx]
	;
_U4LD	proc
	push	ebx
	mov	ebx,edx
	mov	edx,00003FFFh
_U4LD	endp

L4TOLD:
	push	ecx
	test	eax,eax
	jz	L003
	bsr	ecx,eax
	mov	ch,cl
	mov	cl,31
	sub	cl,ch
	shl	eax,cl
	mov	cl,ch
	movzx	ecx,ch
	add	ecx,edx
	mov	edx,eax
	jmp	L004
L003:
	xor	edx,edx
	xor	ecx,ecx
L004:
	xor	eax,eax
	mov	[ebx],eax
	mov	[ebx+4],edx
	mov	[ebx+8],cx
	pop	ecx
	pop	ebx
	ret

	END
