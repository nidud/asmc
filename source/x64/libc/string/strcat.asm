include string.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

strcat	PROC s1:LPSTR, s2:LPSTR
	strlen( rcx )
	add	rax,s1
	strcpy( rax,s2 )
	mov	rax,s1
	ret
strcat	ENDP

	END
