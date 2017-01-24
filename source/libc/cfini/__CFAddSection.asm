include io.inc
include alloc.inc
include cfini.inc

	.code

__CFAddSection PROC USES esi __ini:PCFINI, __section:LPSTR

	.if	__CFGetSection(__ini, __section)

		CFDelEntries(eax)
	.else

		.if	__CFAlloc()

			mov	esi,eax
			mov	[esi].S_CFINI.cf_flag,_CFSECTION
			mov	[esi].S_CFINI.cf_name,salloc(__section)

			mov	eax,__ini
			.if	eax
				.while	[eax].S_CFINI.cf_next

					mov	eax,[eax].S_CFINI.cf_next
				.endw
				mov	[eax].S_CFINI.cf_next,esi
			.endif
			mov	eax,esi
		.endif
	.endif
	ret

__CFAddSection ENDP

	END
