include cfini.inc
include stdio.inc

	.code

CFAddEntryX PROC C ini:PCFINI, format:LPSTR, argptr:VARARG


	.if	ftobufin( format, addr argptr )

		CFAddEntry( ini, edx )
	.endif

	ret

CFAddEntryX ENDP

	END
