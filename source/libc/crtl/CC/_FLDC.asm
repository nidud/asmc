	.486
	.model	flat, c
	.code

_FLDC	proc
	;
	;  CMP long double[EAX], long double[EDX]
	;
	;  0:  A = B
	;  1:  A > B
	; -1:  A < B
	;  2:  NaN
	;
	push	edi
	push	esi
	movsx	esi,word ptr [eax+8]
	or	esi,80000000h
	inc	esi
	jnz	@F
	mov	esi,[eax+4]
	add	esi,esi
	or	esi,[eax]
	jnz	error
@@:
	movsx	esi,word ptr [edx+8]
	or	esi,80000000h
	inc	esi
	jnz	@F
	mov	esi,[edx+4]
	add	esi,esi
	or	esi,[edx]
	jnz	error
@@:
	mov	esi,[eax+6]
	mov	edi,[edx+6]
	xor	edi,esi
	mov	edi,0
	js	L007
	mov	si,[eax+8]
	cmp	si,[edx+8]
	jnz	@F
	mov	edi,[eax+4]
	cmp	edi,[edx+4]
	jnz	@F
	mov	edi,[eax]
	cmp	edi,[edx]
@@:
	mov	edi,0
	jz	toend
	rcr	eax,1
	xor	esi,eax
done:
	add	esi,esi
	sbb	edi,0
	add	edi,edi
	inc	edi
toend:
	mov	eax,edi
	pop	esi
	pop	edi
	ret
error:
	mov	eax,2
	pop	esi
	pop	edi
	ret
L007:
	or	edi,[eax]
	or	edi,[edx]
	or	edi,[eax+4]
	or	edi,[edx+4]
	mov	ax,[eax+8]
	shl	eax,16
	mov	ax,[edx+8]
	and	eax,7FFF7FFFh
	or	eax,edi
	mov	edi,0
	jnz	done
	pop	esi
	pop	edi
	ret
_FLDC	endp

	END
