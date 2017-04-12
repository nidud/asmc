include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

toupper PROC char:SINT
	mov	rax,rcx
	sub	al,'a'
	cmp	al,'z'-'a'+1
	sbb	ah,ah
	and	ah,'a'-'A'
	sub	al,ah
	add	al,'a'
	and	rax,000000FFh
	ret
toupper ENDP

	END

