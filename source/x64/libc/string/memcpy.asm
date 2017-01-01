include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

	.code

memcpy	PROC dst:LPSTR, src:LPSTR, count:SIZE_T

	push	rsi
	push	rdi

	mov	rax,rcx		; dst -- return value
	mov	rsi,rdx		; src
	mov	rcx,r8		; count

	mov	rdi,rax
	rep	movsb

	pop	rdi
	pop	rsi
	ret

memcpy	ENDP

	END
