include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

memset	PROC dst:LPSTR, char:SIZE_T, count:SIZE_T

	push	rdi
	push	rcx

	mov	rdi,rcx
	mov	rax,rdx
	mov	rcx,r8

	rep	stosb

	pop	rax
	pop	rdi
	ret

memset	ENDP

	END
