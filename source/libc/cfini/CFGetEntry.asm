include cfini.inc
include string.inc

	.code

CFGetEntry PROC USES esi edi __ini:PCFINI, __entry:LPSTR

	mov	edx,__ini
	xor	edi,edi
	xor	eax,eax

	.if	[edx].S_CFINI.cf_flag & _CFSECTION

		mov	eax,[edx].S_CFINI.cf_info

		.while	eax

			.if	[eax].S_CFINI.cf_flag & _CFENTRY

				mov	esi,eax
				mov	edx,[eax].S_CFINI.cf_name
				mov	ecx,__entry
				mov	al,[ecx]

				.while	al == [edx]

					.break .if !al

					add	ecx,1
					add	edx,1
					mov	al,[ecx]
				.endw

				.if	al == [edx]

					mov	edx,edi ; mother
					mov	ecx,esi ; entry
					;
					; return value
					;
					mov	eax,[esi].S_CFINI.cf_info
					.break
				.endif

				mov	eax,esi
			.endif
			mov	edi,eax
			mov	eax,[eax].S_CFINI.cf_next
		.endw
	.endif
	ret

CFGetEntry ENDP

	END
