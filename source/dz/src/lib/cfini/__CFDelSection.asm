include io.inc
include alloc.inc
include cfini.inc

	.code

__CFDelSection PROC __ini:PCFINI, __section:LPSTR

	.if	__CFGetSection(__ini, __section)

		.if	edx

			mov	ecx,[eax].S_CFINI.cf_next
			mov	[edx].S_CFINI.cf_next,ecx
		.endif

		.if	free( [CFDelEntries(eax)].S_CFINI.cf_name ) == __ini

			mov	[eax].S_CFINI.cf_flag,0
			mov	[eax].S_CFINI.cf_name,0
		.else
			free  ( eax )
		.endif
		mov	eax,__ini
	.endif
	ret

__CFDelSection ENDP

	END
