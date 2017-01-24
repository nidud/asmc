include cfini.inc

	.code

CFWrite PROC __file:LPSTR

	mov	eax,__CFBase
	.if	eax

		__CFWrite( eax, __file )
	.endif
	ret

CFWrite ENDP

	END
