; _FLDM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

	.486
	.model	flat, c
	.code

_FLDM	proc
	;
	;  long double[EBX] = long double[EAX] * long double[EDX]
	;
	push	esi
	push	ecx
	push	ebx
	mov	esi,[edx+8]
	mov	ecx,[edx+4]
	mov	ebx,[edx]
	shl	esi,16
	mov	si, [eax+8]
	mov	edx,[eax+4]
	mov	eax,[eax]
	call	multiply
	pop	ebx
	mov	[ebx],eax
	mov	[ebx+4],edx
	mov	[ebx+8],si
	pop	ecx
	pop	esi
	ret
_FLDM	endp

L001:
	test	eax,eax
	jnz	L002
	cmp	edx,80000000h
	jnz	L002
	or	ebx,ebx
	jnz	L002
	or	ecx,ecx
	jnz	L002
	mov	esi,0FFFFFFFFh	; -NaN
	sar	edx,1
	ret
L002:
	dec	si
	add	esi,10000h
	jc	L005
	jo	L005
	or	eax,eax
	jnz	L004
	cmp	edx,80000000h
	jnz	L004
	or	esi,esi
	jns	L004
	xor	esi,8000h
L004:
	ret
L005:
	sub	esi,10000h
	cmp	edx,ecx
	jnz	L006
	cmp	eax,ebx
L006:
	ja	L010
	jnz	L009
	or	eax,eax
	jnz	L007
	cmp	edx,80000000h
L007:
	jz	L008
	ret
L008:
	or	si,si
	jns	L009
	xor	esi,edx
L009:
	mov	edx,ecx
	mov	eax,ebx
	shr	esi,16
L010:
	ret
L011:
	sub	esi,10000h
	or	ebx,ebx
	jnz	L014
	cmp	ecx,80000000h
	jnz	L014
	or	eax,eax
	jnz	L013
	or	edx,edx
	jnz	L013
	sar	ecx,1		; -NaN
	mov	esi,0FFFFFFFFh
	jmp	L014
L013:
	or	si,si
	jns	L014
	xor	esi,ecx
L014:
	mov	edx,ecx
	mov	eax,ebx
	shr	esi,16
	ret

multiply:
	add	si,1
	jc	L001
	jo	L001
	add	esi,0FFFFh
	jc	L011
	jo	L011
	sub	esi,10000h
	test	eax,eax
	jnz	L017
	or	edx,edx
	jnz	L017
	add	si,si
	jnz	L016
	ret
L016:
	rcr	si,1
L017:
	or	ecx,ecx
	jnz	L018
	or	ebx,ebx
	jnz	L018
	test	esi,7FFF0000h
	jnz	L018
	sub	eax,eax
	sub	edx,edx
	sub	esi,esi
	ret
L018:
	push	ebp
	push	edi
	xchg	esi,ecx
	mov	edi,ecx
	rol	edi,16
	sar	edi,16
	sar	ecx,16
	and	edi,80007FFFh
	and	ecx,80007FFFh
	add	ecx,edi
	sub	cx,3FFEh
	jc	L019
	cmp	cx,7FFFh
	jc	L019
	jmp	L027
L019:
	cmp	cx,-64
	jge	L020
	sub	eax,eax
	sub	edx,edx
	sub	ecx,ecx
	jmp	L026
L020:
	push	ecx
	sub	ebp,ebp
	push	esi
	push	edx
	push	eax
	mul	ebx
	xchg	esi,eax
	mov	ecx,edx
	pop	edx
	mul	edx
	mov	edi,edx
	add	ecx,eax
	adc	edi,ebp
	adc	ebp,ebp
	pop	eax
	xchg	ebx,eax
	mul	ebx
	add	ecx,eax
	adc	edi,edx
	adc	ebp,0
	mov	eax,ebx
	pop	edx
	mul	edx
	add	eax,edi
	adc	edx,ebp
	mov	ebx,ecx
	pop	ecx
	js	L021
	add	ebx,ebx
	adc	eax,eax
	adc	edx,edx
	dec	cx
L021:
	add	ebx,ebx
	jnc	L023
	jnz	L022
	or	esi,esi
	setne	bl
	shr	ebx,1
	jc	L022
	mov	esi,eax
	shr	esi,1
L022:
	adc	eax,0
	adc	edx,0
	jnc	L023
	rcr	edx,1
	rcr	eax,1
	inc	cx
	cmp	cx,7FFFh
	jz	L027
L023:
	or	cx,cx
	jg	L026
	jnz	L024
	mov	cl,1
	jmp	L025
L024:
	neg	cx
L025:
	sub	ebx,ebx
	shrd	eax,edx,cl
	shrd	edx,ebx,cl
	sub	cx,cx
L026:
	add	ecx,ecx
	rcr	cx,1
	mov	esi,ecx
	pop	edi
	pop	ebp
	ret
L027:
	mov	ecx,00007FFFh
	mov	edx,80000000h
	xor	eax,eax
	jmp	L026

	END
