	.486
	.model	flat, stdcall

PUBLIC	_allshl
PUBLIC	__llshl
PUBLIC	_I8LS
PUBLIC	_U8LS

	.code

_U8LS:
_I8LS:
	mov	ecx,ebx

_allshl:
__llshl:

_shl64	PROC
	cmp	cl,63
	ja	ZERO
	cmp	cl,31
	ja	__63
	shld	edx,eax,cl
	shl	eax,cl
	ret
__63:
	and	ecx,31
	mov	edx,eax
	xor	eax,eax
	shl	edx,cl
	ret
ZERO:
	xor	eax,eax
	xor	edx,edx
	ret
_shl64	ENDP

	END
