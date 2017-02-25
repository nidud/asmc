include string.inc
include alloc.inc
include cfini.inc
include stdlib.inc
include winbase.inc

	.code

__CFExpandCmd PROC USES esi edi __ini:PCFINI, buffer:LPSTR, __file:LPSTR

  local tmp

	mov	tmp,alloca( 0x8000 )
	mov	edi,eax
	mov	esi,eax

	.if	strrchr( strcpy( esi, strfn( __file ) ), '.' )

		.if	BYTE PTR [eax+1] == 0

			mov	BYTE PTR [eax],0
		.else

			lea	esi,[eax+1]
		.endif
	.endif

	.if	CFGetEntry( __ini, esi )

		mov	esi,eax
		strcpy( edi, eax )

		ExpandEnvironmentStrings( esi, edi, 0x8000 - 1 )
		CFExpandMac( edi, __file )
		strxchg( edi, ", ", "\r\n" )
		strcpy( buffer, edi )
	.endif

	ret

__CFExpandCmd ENDP

	END
