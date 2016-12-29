include string.inc

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

ifndef __SSE__

	.code

strlen	PROC string:LPSTR
if 0
	mov	ecx,[esp+4]
	xor	eax,eax
@@:
	cmp	[ecx],al
	jz	exit_0
	cmp	[ecx+1],al
	jz	exit_1
	cmp	[ecx+2],al
	jz	exit_2
	cmp	[ecx+3],al
	jz	exit_3
	cmp	[ecx+4],al
	jz	exit_4
	cmp	[ecx+5],al
	jz	exit_5
	cmp	[ecx+6],al
	jz	exit_6
	cmp	[ecx+7],al
	jz	exit_7

	cmp	[ecx+8],al
	jz	exit_8
	cmp	[ecx+9],al
	jz	exit_9
	cmp	[ecx+10],al
	jz	exit_10
	cmp	[ecx+11],al
	jz	exit_11
	cmp	[ecx+12],al
	jz	exit_12
	cmp	[ecx+13],al
	jz	exit_13
	cmp	[ecx+14],al
	jz	exit_14
	cmp	[ecx+15],al
	jz	exit_15
	add	ecx,16
	jmp	@B

exit_15:
	lea	eax,[ecx+15]
	sub	eax,[esp+4]
	ret	4
exit_14:
	lea	eax,[ecx+14]
	sub	eax,[esp+4]
	ret	4
exit_13:
	lea	eax,[ecx+13]
	sub	eax,[esp+4]
	ret	4
exit_12:
	lea	eax,[ecx+12]
	sub	eax,[esp+4]
	ret	4
exit_11:
	lea	eax,[ecx+11]
	sub	eax,[esp+4]
	ret	4
exit_10:
	lea	eax,[ecx+10]
	sub	eax,[esp+4]
	ret	4
exit_9:
	lea	eax,[ecx+9]
	sub	eax,[esp+4]
	ret	4
exit_8:
	lea	eax,[ecx+8]
	sub	eax,[esp+4]
	ret	4
exit_7:
	lea	eax,[ecx+7]
	sub	eax,[esp+4]
	ret	4
exit_6:
	lea	eax,[ecx+6]
	sub	eax,[esp+4]
	ret	4
exit_5:
	lea	eax,[ecx+5]
	sub	eax,[esp+4]
	ret	4
exit_4:
	lea	eax,[ecx+4]
	sub	eax,[esp+4]
	ret	4
exit_3:
	lea	eax,[ecx+3]
	sub	eax,[esp+4]
	ret	4
exit_2:
	lea	eax,[ecx+2]
	sub	eax,[esp+4]
	ret	4
exit_1:
	lea	eax,[ecx+1]
	sub	eax,[esp+4]
	ret	4
exit_0:
	sub	ecx,[esp+4]
	add	eax,ecx
	ret	4
else
	mov	eax,[esp+4]
	mov	ecx,[esp+4]
	push	edx
	and	ecx,3
	jz	L2
	sub	eax,ecx
	shl	ecx,3
	mov	edx,-1
	shl	edx,cl
	not	edx
	or	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jnz	L3
L1:
	add	eax,4
L2:
	mov	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jz	L1
L3:
	pop	edx
	bsf	ecx,ecx
	shr	ecx,3
	add	eax,ecx
	sub	eax,[esp+4]
	ret	4
endif
strlen	ENDP

else	; SSE2 - Auto install

include math.inc

	.data
	strlen_p dd _rtl_strlen

	.code

strlen_SSE2:

	mov	ecx,[esp+4]	; string

	test	ecx,16-1
	jz	aligned_16

	xor	eax,eax

	cmp	[ecx+0],al
	jz	exit_0
	cmp	[ecx+1],al
	jz	exit_1
	cmp	[ecx+2],al
	jz	exit_2
	cmp	[ecx+3],al
	jz	exit_3
	cmp	[ecx+4],al
	jz	exit_4
	cmp	[ecx+5],al
	jz	exit_5
	cmp	[ecx+6],al
	jz	exit_6
	cmp	[ecx+7],al
	jz	exit_7
	add	eax,8
	cmp	[ecx+8],ah
	jz	exit_0
	cmp	[ecx+9],ah
	jz	exit_1
	cmp	[ecx+10],ah
	jz	exit_2
	cmp	[ecx+11],ah
	jz	exit_3
	cmp	[ecx+12],ah
	jz	exit_4
	cmp	[ecx+13],ah
	jz	exit_5
	cmp	[ecx+14],ah
	jz	exit_6
	cmp	[ecx+15],ah
	jz	exit_7

	add	ecx,10h
	and	ecx,-10h

	ALIGN	4
aligned_16:

	xorps	xmm0,xmm0

	pcmpeqb xmm0,[ecx]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_00

	pcmpeqb xmm0,[ecx+10h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_10

	pcmpeqb xmm0,[ecx+20h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_20

	pcmpeqb xmm0,[ecx+30h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_30

	add	ecx,40h
	and	ecx,-40h

	ALIGN	16
loop_64:
	movaps	xmm1,[ecx]
	movaps	xmm2,[ecx+10h]
	movaps	xmm3,[ecx+20h]
	movaps	xmm4,[ecx+30h]
	pminub	xmm1,xmm2
	pminub	xmm3,xmm4
	pminub	xmm1,xmm3
	pcmpeqb xmm1,xmm0
	pmovmskb eax,xmm1
	add	ecx,40h
	test	eax,eax
	jz	loop_64

	sub	ecx,40h

	pcmpeqb xmm0,[ecx]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_00

	pcmpeqb xmm2,xmm0
	pmovmskb eax,xmm2
	test	eax,eax
	jnz	exit_10

	pcmpeqb xmm0,[ecx+20h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_20

	pcmpeqb xmm0,xmm4
	pmovmskb eax,xmm0

exit_30:
	add	ecx,10h
exit_20:
	add	ecx,10h
exit_10:
	add	ecx,10h
exit_00:
	bsf	eax,eax
	add	eax,ecx
	sub	eax,[esp+4]
	ret	4
exit_40:
	add	ecx,40h
	jmp	exit_00
exit_0:
	test	eax,eax
	ret	4
	ALIGN	4
exit_1:
	add	eax,1
	ret	4
	ALIGN	4
exit_2:
	add	eax,2
	ret	4
	ALIGN	4
exit_3:
	add	eax,3
	ret	4
	ALIGN	4
exit_4:
	add	eax,4
	ret	4
	ALIGN	4
exit_5:
	add	eax,5
	ret	4
	ALIGN	4
exit_6:
	add	eax,6
	ret	4
	ALIGN	4
exit_7:
	add	eax,7
	ret	4

	ALIGN	16

strlen_386:

	mov	ecx,[esp+4]
	xor	eax,eax

	cmp	[ecx+0],al
	jz	exit_0
	cmp	[ecx+1],al
	jz	exit_1
	cmp	[ecx+2],al
	jz	exit_2
	cmp	[ecx+3],al
	jz	exit_3

	and	ecx,-4
	push	edx

	ALIGN	4
@@:
	add	ecx,4
	mov	edx,[ecx]
	lea	eax,[edx-01010101h]
	not	edx
	and	eax,edx
	and	eax,80808080h
	jz	@B
	pop	edx
	bsf	eax,eax
	shr	eax,3
	add	eax,ecx
	sub	eax,[esp+4]
	ret	4

	ALIGN	16

strlen	PROC string:LPSTR
	jmp	strlen_p
strlen	ENDP

	ALIGN	4
	;
	; First call: set pointer and jump
	;
_rtl_strlen:
	mov	eax,strlen_386
	.if	sselevel & SSE_SSE2
		mov eax,strlen_SSE2
	.endif
	mov	strlen_p,eax
	jmp	eax

endif
	END
