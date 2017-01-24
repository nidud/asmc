include alloc.inc
include cfini.inc
include ctype.inc
include string.inc

	.code

CFAddEntry PROC USES esi edi ebx __ini:PCFINI, __string:LPSTR


	xor	edi,edi
	mov	esi,__string

	movzx	eax,byte ptr [esi]
	.while	__ctype[eax+1] & _SPACE

		add	esi,1
		mov	al,[esi]
	.endw

	.if	al == ';'

		.if	__CFAlloc()

			mov	edi,eax
			strtrim(esi)
			mov	[edi].S_CFINI.cf_flag,_CFCOMMENT
			mov	[edi].S_CFINI.cf_name,salloc(esi)
		.endif

	.elseif strchr(esi, '=')

		mov	byte ptr [eax],0
		lea	edi,[eax+1]

		movzx	eax,byte ptr [edi]
		.while	__ctype[eax+1] & _SPACE

			add	edi,1
			mov	al,[edi]
		.endw

		.if	strtrim(esi)

			mov	ebx,eax
			.if	strtrim(edi)

				lea	ebx,[ebx+eax+2]
				.if	CFGetEntry( __ini, esi )

					free( [eax].S_CFINI.cf_name )
				.else

					__CFAlloc()
				.endif

				.if	eax

					xchg	ebx,eax
					.if	malloc( eax )

						mov	[ebx].S_CFINI.cf_name,eax
						strcat( strcat( strcpy( eax, esi ), "=" ), edi )
						strchr( eax, '=' )
						mov	byte ptr [eax],0
						inc	eax
						mov	[ebx].S_CFINI.cf_info,eax

						mov	eax,ebx
						test	[ebx].S_CFINI.cf_flag,_CFENTRY
						jnz	toend

						mov	edi,ebx
						mov	[ebx].S_CFINI.cf_flag,_CFENTRY
					.endif
				.endif
			.endif
		.endif
	.endif

	.if	eax

		mov	eax,edi
		mov	ebx,__ini
		mov	edx,[ebx].S_CFINI.cf_info
		.if	edx

			.while	[edx].S_CFINI.cf_next

				mov	edx,[edx].S_CFINI.cf_next
			.endw
			mov	[edx].S_CFINI.cf_next,eax
		.else

			mov	[ebx].S_CFINI.cf_info,eax
		.endif
	.endif
toend:
	ret

CFAddEntry ENDP

	END
