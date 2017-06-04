include crtl.inc
include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strext	PROC string:LPSTR
	push	ecx
	mov	eax,[esp+4+4]
	strfn  (eax)
	push	eax
	strrchr(eax, '.')
	pop	ecx
	test	eax,eax
	jz	@F
	cmp	eax,ecx
	jne	@F
	sub	eax,eax
@@:
	pop	ecx
	ret
strext	ENDP

	END
