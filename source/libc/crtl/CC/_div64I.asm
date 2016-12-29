	.486
	.model	flat, stdcall

public	_I8D
public	_div64I

_div64U proto

	.code
	;
	; edx:eax.ecx:ebx = edx:eax / ecx:ebx
	;
_I8D:

_div64I PROC
	test	edx,edx		; hi word of dividend
	js	dividend	; signed ?
	or	ecx,ecx		; hi word of divisor
	js	divisor		; signed ?
	call	_div64U
	ret
divisor:
	neg	ecx
	neg	ebx
	sbb	ecx,0
	call	_div64U
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
	call	_div64U
	neg	ecx
	neg	ebx
	sbb	ecx,0
	ret
@@:
	call	_div64U
	neg	ecx
	neg	ebx
	sbb	ecx,0
	neg	edx
	neg	eax
	sbb	edx,0
	ret
_div64I ENDP

	END
