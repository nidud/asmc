include string.inc

	.code

strcat	PROC s1:LPSTR, s2:LPSTR
	strlen( s1 )
	add	eax,s1
	strcpy( eax,s2 )
	mov	eax,s1
	ret
strcat	ENDP

	END
