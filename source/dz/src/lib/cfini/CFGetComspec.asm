include cfini.inc

	.code

CFGetComspec PROC value:UINT

	mov	eax,__CFBase
	.if	eax

		__CFGetComspec( eax, value )
	.endif
	ret

CFGetComspec ENDP

	END
