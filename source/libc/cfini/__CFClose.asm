include alloc.inc
include cfini.inc

	.code

	ASSUME	esi:PTR S_CFINI
	ASSUME	edi:PTR S_CFINI

__CFClose PROC USES esi edi ebx __ini:PCFINI

	mov	esi,__ini

	.while	esi

		.if	[esi].cf_name

			free([esi].cf_name)
		.endif

		mov	edi,[esi].cf_info
		.while	edi

			.if	[edi].cf_name

				free([edi].cf_name)
			.endif

			mov	eax,edi
			mov	edi,[edi].cf_next
			free  ( eax )
		.endw

		mov	eax,esi
		mov	esi,[esi].cf_next
		free  ( eax )
	.endw
	ret

__CFClose ENDP

	END
