include ctype.inc

	.code

	option stackbase:esp

tolower PROC char:SINT
	mov	eax,[esp+4]
	sub	al,'A'
	cmp	al,'Z'-'A'+1
	sbb	ah,ah
	and	ah,'a'-'A'
	add	al,ah
	add	al,'A'
	and	eax,000000FFh
	ret
tolower ENDP

	END

