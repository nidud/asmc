include cfini.inc

	.code

CFAddSection PROC __section:LPSTR

	mov	eax,__CFBase
	.if	eax

		__CFAddSection( eax, __section )
	.endif
	ret

CFAddSection ENDP

	END
