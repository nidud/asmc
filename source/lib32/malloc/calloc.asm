include malloc.inc

	.code

calloc	PROC n, nsize
	mov eax,n
	mul nsize
	malloc(eax)
	ret
calloc	ENDP

	END
