include string.inc
ifdef __SSE__

	.code

option	stackbase:esp

memcpy_sse proc uses esi edi dst:LPSTR, src:LPSTR, count:SIZE_T

	mov	eax,dst			; -- return value
	mov	esi,src
	mov	ecx,count

	test	ecx,ecx
	jz	toend			; 0
	test	ecx,-2
	jz	copy_1			; 1
	test	ecx,-4
	jz	copy_2			; 2..3
	test	ecx,-8
	jz	copy_4			; 4..7
	test	ecx,-16
	jz	copy_8			; 8..15
	test	ecx,-32
	;
	; 16..n byte
	;
	movdqu	xmm3,[esi]		; save aligned and tail bytes
	movdqu	xmm5,[esi+ecx-16]
	jz	copy_16			; 16..31
	;
	; 32..n byte
	;
	test	ecx,-64
	movdqu	xmm4,[esi+16]
	movdqu	xmm6,[esi+ecx-32]
	jz	copy_32			; 32..63
	;
	; >= 64 byte
	;
	mov	edi,eax			; align pointer
	neg	edi
	and	edi,32-1
	add	esi,edi
	sub	ecx,edi
	add	edi,eax
	and	ecx,-32
	cmp	esi,edi
	ja	move_R
	ALIGN	16
loop_L:
	sub	ecx,32
	movups	xmm1,[esi+ecx]		; copy 32 bytes
	movups	xmm2,[esi+ecx+16]
	movaps	[edi+ecx],xmm1
	movaps	[edi+ecx+16],xmm2
	jnz	loop_L
	jmp	fixup_32
	ALIGN	4
copy_1:
	mov	cl,[esi]
	mov	[eax],cl
	jmp	toend
	ALIGN	4
copy_2:
	mov	di,[esi]
	mov	si,[esi+ecx-2]
	mov	[eax+ecx-2],si
	mov	[eax],di
	jmp	toend
	ALIGN	8
copy_4:
	mov	edi,[esi]
	mov	esi,[esi+ecx-4]
	mov	[eax],edi
	mov	[eax+ecx-4],esi
	jmp	toend
	ALIGN	8
move_R:
	lea	edi,[edi+ecx]
	lea	esi,[esi+ecx]
	neg	ecx
	ALIGN	16
loop_R:
	movups	xmm1,[esi+ecx]
	movups	xmm2,[esi+ecx+16]
	movaps	[edi+ecx],xmm1
	movaps	[edi+ecx+16],xmm2
	add	ecx,32
	jnz	loop_R
fixup_32:
	mov	ecx,count		; fixup after copy
	movups	[eax],xmm3		; 0..31 unaligned from start
	movups	[eax+16],xmm4		;
	movups	[eax+ecx-16],xmm5	; 0..31 unaligned tail bytes
	movups	[eax+ecx-32],xmm6	;
toend:
	ret
copy_8:
	movq	xmm2,[esi]
	movq	xmm1,[esi+ecx-8]
	movq	[eax],xmm2
	movq	[eax+ecx-8],xmm1
	jmp	toend
copy_32:
	movups	[eax+16],xmm4
	movups	[eax+ecx-32],xmm6
copy_16:
	movups	[eax],xmm3
	movups	[eax+ecx-16],xmm5
	jmp	toend

memcpy_sse endp
endif
	END
