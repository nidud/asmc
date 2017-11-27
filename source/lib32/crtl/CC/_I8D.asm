	.486
	.model	flat, c

_U8D	proto

	.code
	;
	; edx:eax.ecx:ebx = edx:eax / ecx:ebx
	;
_I8D	proc

	test	edx,edx		; hi word of dividend
	js	dividend	; signed ?
	or	ecx,ecx		; hi word of divisor
	js	divisor		; signed ?
	jmp	_U8D

divisor:
	neg	ecx
	neg	ebx
	sbb	ecx,0
	call	_U8D
	neg	edx
	neg	eax
	sbb	edx,0
	ret
dividend:
	neg	edx
	neg	eax
	sbb	edx,0
	test	ecx,ecx
	jns	@F
	neg	ecx
	neg	ebx
	sbb	ecx,0
	call	_U8D
	neg	ecx
	neg	ebx
	sbb	ecx,0
	ret
@@:
	call	_U8D
	neg	ecx
	neg	ebx
	sbb	ecx,0
	neg	edx
	neg	eax
	sbb	edx,0
	ret
_I8D	endp

	END
