include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

memset	PROC dst:LPSTR, char:SIZE_T, count:SIZE_T

	push	edi

	mov	edi,4[esp+4]
	mov	eax,4[esp+8]
	mov	ecx,4[esp+12]

	rep	stosb

	mov	eax,4[esp+4]
	pop	edi
	ret	12

memset	ENDP

	END
