include alloc.inc
include cfini.inc

	.code

__CFAlloc PROC

	.if	malloc(sizeof(S_CFINI))

		mov	ecx,0
		mov	[eax].S_CFINI.cf_flag,ecx
		mov	[eax].S_CFINI.cf_name,ecx
		mov	[eax].S_CFINI.cf_info,ecx
		mov	[eax].S_CFINI.cf_next,ecx
	.endif
	ret

__CFAlloc ENDP

	END
