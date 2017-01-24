include cfini.inc

	.code

CFRead	PROC __file:LPSTR


	mov	__CFBase,__CFRead( __CFBase, __file )

	ret

CFRead	ENDP

	END
