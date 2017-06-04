include cfini.inc
include stdio.inc

	.code

CFAddSectionX PROC C format:LPSTR, argptr:VARARG


	mov	eax,__CFBase
	.if	eax

		.if	ftobufin( format, addr argptr )

			__CFAddSection( __CFBase, edx )
		.endif
	.endif

	ret

CFAddSectionX ENDP

	END
