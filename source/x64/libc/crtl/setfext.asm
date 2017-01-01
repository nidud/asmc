include string.inc

	.code

	OPTION	WIN64:3, STACKBASE:rsp

setfext PROC path:LPSTR, ext:LPSTR
	strext( rcx )
	test	rax,rax
	jz	@F
	mov	byte ptr [rax],0
@@:
	strcat( path, ext )
	ret
setfext ENDP

	END
