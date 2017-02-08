include cfini.inc
include string.inc

	.code

__CFGetSection PROC USES esi edi ini:PCFINI, section:LPSTR

	mov	eax,ini
	xor	edi,edi

	.while	eax

		.if	[eax].S_CFINI.cf_flag & _CFSECTION

			mov	esi,eax
			.if	!strcmp([esi].S_CFINI.cf_name, section)
if 0
				.if	edi

					mov	ecx,[esi].S_CFINI.cf_next
					mov	[edi].S_CFINI.cf_next,ecx

					mov	eax,ini
					mov	ecx,[eax].S_CFINI.cf_next
					mov	[eax].S_CFINI.cf_next,esi
					mov	[esi].S_CFINI.cf_next,ecx
				.endif
endif
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
