include string.inc

	.code

fmemzero PROC FASTCALL dst, count
	xchg	ecx,edx
	xor	eax,eax
	jmp	start
	ALIGN	4
do_16:
	sub	ecx,16
	mov	[edx+ecx],eax
	mov	[edx+ecx+4],eax
	mov	[edx+ecx+8],eax
	mov	[edx+ecx+12],eax
start:
	cmp	ecx,16
	jae	do_16
	cmp	ecx,8
	jb	@F
	sub	ecx,8
	mov	[edx+ecx],eax
	mov	[edx+ecx+4],eax
@@:
	test	ecx,ecx
	jz	toend
@@:
	sub	ecx,1
	mov	[edx+ecx],al
	jnz	@B
toend:
	mov	eax,edx
	ret
fmemzero ENDP

	END
