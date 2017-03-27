; __llshl.asm - long shift left
;
; signed and unsigned are same
;
	.386
	.model	flat, stdcall

public	_I8LS	; Watcom
public	_U8LS
public	_allshl ; Microsoft
public	__llshl

	.code

_U8LS:
_I8LS:
	mov ecx,ebx	; edx:eax << bl

_allshl:		; edx:eax << cl
__llshl:

	.if cl < 64

		.if cl < 32

			shld edx,eax,cl
			shl eax,cl
			ret
		.endif

		and ecx,31
		mov edx,eax
		xor eax,eax
		shl edx,cl
		ret
	.endif

	xor eax,eax
	xor edx,edx
	ret

	END
