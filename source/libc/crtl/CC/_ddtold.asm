	.486
	.model	flat, stdcall

public _U4LD
public _I4LD

	.code
	;
	; long [eax] to long double[edx]
	;
_I4LD:

_s4told PROC
	test	eax,eax
	jns	_u4told
	push	ebx
	mov	ebx,edx
	neg	eax
	mov	edx,0000BFFFh
	jmp	L4TOLD
_s4told ENDP
	;
	; DWORD [eax] to long double[edx]
	;
_U4LD:

_u4told PROC
	push	ebx
	mov	ebx,edx
	mov	edx,00003FFFh
_u4told ENDP

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
