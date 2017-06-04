	.486
	.model	flat, c

PUBLIC	_U8RS
PUBLIC	_aullshr
PUBLIC	__ullshr

	.code

_U8RS:
	mov	ecx,ebx

_aullshr:
__ullshr:

	cmp	cl,63
	ja	ZERO
	cmp	cl,31
	ja	__U63
	shrd	eax,edx,cl
	shr	edx,cl
	ret
__U63:
	mov	eax,edx
	xor	edx,edx
	and	cl,31
	shr	eax,cl
	ret
ZERO:
	xor	eax,eax
	xor	edx,edx
	ret

	END
