include cfini.inc
include string.inc

	.code

CFGetSection PROC __section:LPSTR

	mov	eax,__CFBase
	.if	eax

		__CFGetSection( eax, __section )
	.endif
	ret

CFGetSection ENDP

	END
