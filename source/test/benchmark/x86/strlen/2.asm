	.686
	.xmm
	.model flat
	.code

	mov	eax,[esp+4]
	mov	ecx,eax
	and	eax,-32
	and	ecx,32-1
	or	edx,-1
	shl	edx,cl
	pxor	xmm0,xmm0
	pcmpeqb xmm0,[eax]
	pmovmskb ecx,xmm0
	and	ecx,edx
	jnz	done
	xorps	xmm0,xmm0
	pcmpeqb xmm0,[eax+16]
	pmovmskb ecx,xmm0
	pxor	xmm2,xmm2
	shl	ecx,16
	and	ecx,edx
	jnz	done
@@:
	movdqa	xmm1,[eax+30h]
	movdqa	xmm0,[eax+20h]
	pcmpeqb xmm0,xmm2
	pmovmskb edx,xmm0
	lea	eax,[eax+20h]
	pcmpeqb xmm1,xmm2
	pmovmskb ecx,xmm1
	shl	ecx,16
	or	ecx,edx
	jz	@B
done:
	bsf	ecx,ecx
	add	eax,ecx
	sub	eax,[esp+4]
	ret

	END
