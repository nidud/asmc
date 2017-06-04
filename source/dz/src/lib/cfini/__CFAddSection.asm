include io.inc
include alloc.inc
include cfini.inc

	.code

__CFAddSection PROC USES esi ini:PCFINI, section:LPSTR

	.if	!__CFGetSection(ini, section)

		.if	__CFAlloc()

			mov	esi,eax
			mov	[esi].S_CFINI.cf_flag,_CFSECTION
			mov	[esi].S_CFINI.cf_name,salloc(section)

			mov	eax,ini
			.if	eax
if 0
				mov	ecx,[eax].S_CFINI.cf_next
				mov	[eax].S_CFINI.cf_next,esi
				mov	[esi].S_CFINI.cf_next,ecx
else
				.while	[eax].S_CFINI.cf_next

					mov	eax,[eax].S_CFINI.cf_next
				.endw
				mov	[eax].S_CFINI.cf_next,esi
endif
			.endif
			mov	eax,esi
		.endif
	.endif
	ret

__CFAddSection ENDP

	END
