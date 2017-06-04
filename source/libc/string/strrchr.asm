include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strrchr PROC string:LPSTR, char:SIZE_T

	push	edi
	mov	edi,4[esp+4]

	xor	eax,eax
	mov	ecx,-1
	repne	scasb
	not	ecx
	dec	edi
	mov	al,4[esp+8]
	std
	repne	scasb
	cld
	mov	al,0
	jne	@F
	lea	eax,[edi+1]
@@:
	test	eax,eax
	pop	edi
	ret

strrchr endp

	END
