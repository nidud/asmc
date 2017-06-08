include crtl.inc
include string.inc

	.code

	option stackbase:esp

strext	proc uses ecx string:LPSTR
	mov	eax,string
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
	ret
strext	endp

	END
