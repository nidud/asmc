include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strchr	PROC string:LPSTR, char:SIZE_T

	xor	rax,rax
@@:
	mov	al,[rcx]
	test	al,al
	jz	toend

	inc	rcx
	cmp	al,dl
	jne	@B

	mov	rax,rcx
	dec	rax
toend:
	ret

strchr	ENDP

	END
