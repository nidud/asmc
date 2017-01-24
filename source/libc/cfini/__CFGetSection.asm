include cfini.inc
include string.inc

	.code

__CFGetSection PROC USES esi edi __ini:PCFINI, __section:LPSTR

	mov	eax,__ini
	xor	edi,edi

	.while	eax

		.if	[eax].S_CFINI.cf_flag & _CFSECTION

			mov	esi,eax
			.if	!strcmp([esi].S_CFINI.cf_name, __section)

				mov	edx,edi
				mov	eax,esi
				.break
			.endif
			mov	eax,esi
		.endif
		mov	edi,eax
		mov	eax,[eax].S_CFINI.cf_next
	.endw
	ret

__CFGetSection ENDP

	END
