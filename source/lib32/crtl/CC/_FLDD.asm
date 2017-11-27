	.486
	.model	flat, c
	.code

_FLDD	proc ; long double[EBX] = long double[EAX] / long double[EDX]
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
	call	divide
	pop	ebx
	mov	[ebx],eax
	mov	[ebx+4],edx
	mov	[ebx+8],si
	pop	ecx
	pop	esi
	ret
_FLDD	endp

L001:
	dec	si
	add	esi,10000h
	jc	L004
	jo	L004
	jns	L003
	test	eax,eax
	jnz	L003
	cmp	edx,80000000h
	jnz	L003
	xor	esi,8000h
L003:
	ret
L004:
	sub	esi,10000h
	test	eax,eax
	jnz	L005
	test	ebx,ebx
	jnz	L005
	cmp	edx,80000000h
	jnz	L005
	cmp	ecx,edx
	jnz	L005
	sar	edx,1
	mov	esi,0FFFFh
	ret
L005:
	cmp	edx,ecx
	jnz	L006
	cmp	eax,ebx
L006:
	ja	L007
	mov	edx,ecx
	mov	eax,ebx
	shr	esi,16
L007:
	ret
L008:
	sub	esi,10000h
	or	ebx,ebx
	jnz	L009
	cmp	ecx,80000000h
	jnz	L009
	mov	eax,esi
	shl	eax,16
	xor	esi,eax
	and	esi,ecx
	sub	ecx,ecx
L009:
	mov	edx,ecx
	mov	eax,ebx
	shr	esi,16
	ret
divide:
	add	si,1		; add 1 to exponent
	jc	L001
	jo	L001
	add	esi,0FFFFh
	jc	L008
	jo	L008
	sub	esi,10000h
	or	ecx,ecx
	jnz	L013
	or	ebx,ebx
	jnz	L013
	test	esi,7FFF0000h
	jnz	L013
	or	eax,eax
	jnz	L011
	or	edx,edx
	jnz	L011
	mov	eax,esi
	add	ax,ax
	jnz	L011
	int	3		; Invalid operation
	mov	edx,0C0000000h
	sub	eax,eax
	mov	esi,0FFFFh
	ret
L011:
	int	3		; zero divide
	mov	edx,80000000h
	sub	eax,eax
	or	esi,7FFFh
	ret
L013:
	or	eax,eax
	jnz	L015
	or	edx,edx
	jnz	L015
	add	si,si
	jnz	L014
	ret
L014:
	rcr	si,1
L015:
	push	ebp
	mov	ebp,esp
	push	edi
	xchg	esi,ecx
	mov	edi,ecx
	rol	edi,16
	sar	edi,16
	sar	ecx,16
	and	edi,80007FFFh
	and	ecx,80007FFFh
	rol	edi,16
	rol	ecx,16
	add	di,cx
	rol	edi,16
	rol	ecx,16
	or	di,di
	jnz	L017
L016:
	add	eax,eax
	adc	edx,edx
	dec	di
	or	edx,edx
	jns	L016
L017:
	or	cx, cx
	jnz	L019
L018:
	add	ebx, ebx
	adc	esi, esi
	dec	cx
	or	esi, esi
	jns	L018
L019:
	sub	di,cx
	add	di,3FFFh
	js	L020
	cmp	di,7FFFh
	jc	L020
	mov	edi,ecx
	mov	di,7FFFh
	mov	edx,80000000h
	sub	eax,eax
	jmp	L032
L020:
	cmp	di,-64
	jge	L021
	sub	eax,eax
	sub	edx,edx
	sub	edi,edi
	jmp	L032
L021:
	push	edi	; [ebp-8]  - exponent A
	push	esi	; [ebp-12] - high B
	push	ebx	; [ebp-16] - low B
	mov	ecx,esi ; ecx: high B
	mov	edi,edx ; edi: high A
	mov	esi,eax ; esi: low A
	sub	eax,eax ; LA = 0
	cmp	ecx,edi ; HB >= HA ?
	ja	L022
	sub	edx,ecx ; HA -= HB
	inc	eax	; LA = 1
L022:
	push	eax	; [ebp-20] save LA
	mov	eax,esi
	div	ecx	; [LA] / HB
	push	eax	; [ebp-24]
	xchg	ebx,eax
	mul	ebx
	xchg	ecx,eax
	xchg	edx,ebx
	mul	edx
	add	eax,ebx
	adc	edx,0
	mov	ebx,[ebp-16]
	test	byte ptr [ebp-20],1
	jz	L023
	add	eax,ebx
	adc	edx,[ebp-12]
L023:
	neg	ecx
	sbb	esi,eax
	sbb	edi,edx
	jz	L025
L024:
	sub	dword ptr [ebp-24],1
	sbb	dword ptr [ebp-20],0
	add	ecx,ebx
	adc	esi,[ebp-12]
	adc	edi,0
	jnz	L024
L025:
	mov	edi,esi
	mov	esi,ecx
	mov	ecx,[ebp-12]
	cmp	ecx,edi
	ja	L026
	sub	edi, ecx
	add	dword ptr [ebp-24],1
	adc	dword ptr [ebp-20],0
L026:
	mov	edx, edi
	mov	eax, esi
	div	ecx
	push	eax		; [ebp-28]
	or	eax, eax
	jz	L028
	xchg	ebx, eax
	mul	ebx
	xchg	ecx, eax
	xchg	edx, ebx
	mul	edx
	add	eax, ebx
	adc	edx, 0
	neg	ecx
	sbb	esi, eax
	sbb	edi, edx
	jz	L028
L027:
	sub	dword ptr [ebp-28],1
	sbb	dword ptr [ebp-24],0
	sbb	dword ptr [ebp-20],0
	add	ecx,[ebp-16]
	adc	esi,[ebp-12]
	adc	edi,0
	jnz	L027
L028:
	pop	eax
	pop	edx
	pop	ebx
	add	esp,8
	pop	edi
	dec	di
	shr	ebx,1
	jnc	L029
	rcr	edx,1
	rcr	eax,1
	inc	edi
L029:
	or	di,di
	jg	L032
	jnz	L030
	mov	cl,1
	jmp	L031
L030:
	neg	di
	mov	cx,di
L031:
	sub	ebx,ebx
	shrd	eax,edx,cl
	shrd	edx,ebx,cl
	xor	di,di
L032:
	add	edi,edi
	rcr	di,1
	mov	esi,edi
	pop	edi
	pop	ebp
	ret

	END
