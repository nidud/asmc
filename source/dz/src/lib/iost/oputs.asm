include stdio.inc
include iost.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

oputs	PROC string:LPSTR
	push	edx
	mov	edx,[esp+8]
@@:
	mov	al,[edx]
	inc	edx
	test	al,al
	jz	@F
	call	oputc
	jnz	toend
	jmp	@B
@@:
	mov	eax,0Dh
	call	oputc
	jz	toend
	mov	eax,0Ah
	call	oputc
toend:
	pop	edx
	ret	4
oputs	ENDP

	END
