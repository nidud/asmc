	.486
	.model	flat, stdcall

PUBLIC	_aullshr
PUBLIC	__ullshr
PUBLIC	_U8RS

	.code

_U8RS:
	mov	ecx,ebx
_aullshr:
__ullshr:
_shr64U PROC
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
_shr64U ENDP

	END
