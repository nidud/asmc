
	.x64
	.model	flat, fastcall

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strlen	PROC string:QWORD

	mov	r8,rcx

	test	rcx,16-1
	jz	aligned_16

	xor	rax,rax

	cmp	[rcx+0],al
	jz	exit_0
	cmp	[rcx+1],al
	jz	exit_1
	cmp	[rcx+2],al
	jz	exit_2
	cmp	[rcx+3],al
	jz	exit_3
	cmp	[rcx+4],al
	jz	exit_4
	cmp	[rcx+5],al
	jz	exit_5
	cmp	[rcx+6],al
	jz	exit_6
	cmp	[rcx+7],al
	jz	exit_7
	add	rax,8
	cmp	[rcx+8],ah
	jz	exit_0
	cmp	[rcx+9],ah
	jz	exit_1
	cmp	[rcx+10],ah
	jz	exit_2
	cmp	[rcx+11],ah
	jz	exit_3
	cmp	[rcx+12],ah
	jz	exit_4
	cmp	[rcx+13],ah
	jz	exit_5
	cmp	[rcx+14],ah
	jz	exit_6
	cmp	[rcx+15],ah
	jz	exit_7

	add	rcx,10h
	and	rcx,-10h

	ALIGN	4
aligned_16:

	xorps	xmm0,xmm0

	pcmpeqb xmm0,[rcx]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_00

	pcmpeqb xmm0,[rcx+10h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_10

	pcmpeqb xmm0,[rcx+20h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_20

	pcmpeqb xmm0,[rcx+30h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_30

	add	rcx,40h
	and	rcx,-40h

	ALIGN	16
loop_64:
	movaps	xmm1,[rcx]
	movaps	xmm2,[rcx+10h]
	movaps	xmm3,[rcx+20h]
	movaps	xmm4,[rcx+30h]
	pminub	xmm1,xmm2
	pminub	xmm3,xmm4
	pminub	xmm1,xmm3
	pcmpeqb xmm1,xmm0
	pmovmskb eax,xmm1
	add	rcx,40h
	test	eax,eax
	jz	loop_64

	sub	rcx,40h

	pcmpeqb xmm0,[rcx]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_00

	pcmpeqb xmm2,xmm0
	pmovmskb eax,xmm2
	test	eax,eax
	jnz	exit_10

	pcmpeqb xmm0,[rcx+20h]
	pmovmskb eax,xmm0
	test	eax,eax
	jnz	exit_20

	pcmpeqb xmm0,xmm4
	pmovmskb eax,xmm0

exit_30:
	add	rcx,10h
exit_20:
	add	rcx,10h
exit_10:
	add	rcx,10h
exit_00:
	bsf	rax,rax
	add	rax,rcx
	sub	rax,r8
	ret
exit_40:
	add	rcx,40h
	jmp	exit_00
exit_0:
	test	rax,rax
	ret
	ALIGN	4
exit_1:
	add	rax,1
	ret
	ALIGN	4
exit_2:
	add	rax,2
	ret
	ALIGN	4
exit_3:
	add	rax,3
	ret
	ALIGN	4
exit_4:
	add	rax,4
	ret
	ALIGN	4
exit_5:
	add	rax,5
	ret
	ALIGN	4
exit_6:
	add	rax,6
	ret
	ALIGN	4
exit_7:
	add	rax,7
	ret

strlen	ENDP

	END
