include ctype.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

tolower PROC char:SIZE_T
	mov	rax,rcx
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	ah,ah
	and	ah,'a'-'A'
	add	al,ah
	add	al,'A'
	and	rax,000000FFh
	ret
tolower ENDP

	END

