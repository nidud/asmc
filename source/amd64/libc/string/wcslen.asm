include string.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

wcslen	PROC string:LPWSTR
	xor	eax,eax
	mov	rdx,rdi
	mov	rdi,rcx
	or	rcx,-1
	repne	scasw
	mov	rdi,rdx
	not	rcx
	dec	rcx
	mov	rax,rcx
	ret
wcslen	ENDP

	END
