include cfini.inc

	.code

CFGetSectionID PROC __section:LPSTR, __id:UINT

	mov	eax,__CFBase
	.if	eax

		.if	__CFGetSection( eax, __section )

			CFGetEntryID( eax, __id )
		.endif
	.endif
	ret

CFGetSectionID ENDP

	END
