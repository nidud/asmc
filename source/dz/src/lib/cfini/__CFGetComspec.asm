include stdlib.inc
include alloc.inc
include io.inc
include cfini.inc
include string.inc
include process.inc
include dzlib.inc

extern	__comspec:byte

	.code

__CFGetComspec PROC USES esi edi ebx __ini:PCFINI, value:UINT

local	buffer[512]:BYTE

	mov esi,value
	mov comspec_type,esi

	__initcomspec()
	strcpy( __pCommandArg, "/C" )

	.if esi

		.if __CFGetSection( __ini, addr __comspec )

			mov esi,eax
			lea ebx,buffer

			.if CFGetEntryID( esi, 0 )

				.if !_access(expenviron(strcpy(ebx, eax)), 0)

					free(__pCommandCom)
					mov __pCommandCom,salloc(ebx)

					mov eax,__pCommandArg
					mov byte ptr [eax],0

					.if CFGetEntryID(esi, 1)

						expenviron(strcpy(ebx, eax))
						strncpy(__pCommandArg, eax, 64-1)
					.endif
				.endif
			.endif
		.endif
	.endif
	mov	eax,__pCommandCom
	ret

__CFGetComspec ENDP

	END
