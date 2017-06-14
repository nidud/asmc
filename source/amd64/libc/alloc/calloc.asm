include alloc.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

calloc	PROC n, nsize
	mov	eax,ecx
	mul	edx
	malloc( eax )
	ret
calloc	ENDP

	END
