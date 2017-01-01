include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strext	PROC string:LPSTR

	strfn ( rcx )
	push	rax
	strrchr( rax, '.' )
	pop	rcx
	jz	@F
	cmp	rax,rcx
	jne	@F
	xor	rax,rax
@@:

	ret
strext	ENDP

	END
