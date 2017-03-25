include string.inc

ifdef __SSE__

	.code

	option	stackbase:esp

strlen_sse proc string:LPSTR

	mov	ecx,string
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
	sub	eax,string
	ret
exit_40:
	add	ecx,40h
	jmp	exit_00
exit_0:
	test	eax,eax
	ret
	ALIGN	4
exit_1:
	add	eax,1
	ret
	ALIGN	4
exit_2:
	add	eax,2
	ret
	ALIGN	4
exit_3:
	add	eax,3
	ret
	ALIGN	4
exit_4:
	add	eax,4
	ret
	ALIGN	4
exit_5:
	add	eax,5
	ret
	ALIGN	4
exit_6:
	add	eax,6
	ret
	ALIGN	4
exit_7:
	add	eax,7
	ret
strlen_sse endp
endif
	END
