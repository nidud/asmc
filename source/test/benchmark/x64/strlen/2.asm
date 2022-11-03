	.code

	mov	rax,rcx
	mov	r8,rcx
	and	rax,-32
	and	ecx,32-1
	or	edx,-1
	shl	edx,cl
	pxor	xmm0,xmm0
	pcmpeqb xmm0,[rax]
	pmovmskb ecx,xmm0
	and	ecx,edx
	jnz	done
	xorps	xmm0,xmm0
	pcmpeqb xmm0,[rax+16]
	pmovmskb ecx,xmm0
	pxor	xmm2,xmm2
	shl	ecx,16
	and	ecx,edx
	jnz	done
@@:
	movdqa	xmm1,[rax+30h]
	movdqa	xmm0,[rax+20h]
	pcmpeqb xmm0,xmm2
	pmovmskb edx,xmm0
	lea	rax,[rax+20h]
	pcmpeqb xmm1,xmm2
	pmovmskb ecx,xmm1
	shl	ecx,16
	or	ecx,edx
	jz	@B
done:
	bsf	ecx,ecx
	add	rax,rcx
	sub	rax,r8
	ret

	END
