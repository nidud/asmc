include alloc.inc
include cfini.inc
include ctype.inc
include string.inc

	.code

CFAddEntry PROC USES esi edi ebx cf:PCFINI, string:LPSTR

	xor	edi,edi
	mov	esi,string

	movzx	eax,byte ptr [esi]
	.while	__ctype[eax+1] & _SPACE

		add	esi,1
		mov	al,[esi]
	.endw

	.repeat

		.if	al == ';'

			.break .if !__CFAlloc()

			mov	edi,eax
			strtrim(esi)
			mov	[edi].S_CFINI.cf_flag,_CFCOMMENT
			mov	[edi].S_CFINI.cf_name,salloc(esi)
			mov	eax,edi

		.elseif strchr(esi, '=')

			mov	byte ptr [eax],0
			lea	edi,[eax+1]

			movzx	eax,byte ptr [edi]
			.while	__ctype[eax+1] & _SPACE

				add	edi,1
				mov	al,[edi]
			.endw

			.break .if !strtrim(esi)
			mov	ebx,eax
			.break .if !strtrim(edi)
			lea	ebx,[ebx+eax+2]

			.if	CFGetEntry( cf, esi )

				mov	eax,[ecx].S_CFINI.cf_next
				.if	!edx

					mov	edx,cf
					mov	[edx].S_CFINI.cf_info,eax
				.else
					mov	[edx].S_CFINI.cf_next,eax
				.endif
				mov	eax,ecx
				free  ( [ecx].S_CFINI.cf_name )
				free  ( eax )
			.endif

			.break .if !__CFAlloc()

			xchg	ebx,eax
			.break .if !malloc( eax )

			mov	[ebx].S_CFINI.cf_name,eax
			strcat( strcat( strcpy( eax, esi ), "=" ), edi )
			strchr( eax, '=' )
			mov	byte ptr [eax],0
			inc	eax
			mov	[ebx].S_CFINI.cf_info,eax

			mov	eax,ebx
			mov	[eax].S_CFINI.cf_flag,_CFENTRY
		.endif

		mov	edx,cf
		mov	ecx,[edx].S_CFINI.cf_info
if 0
		mov	[eax].S_CFINI.cf_next,ecx
		mov	[edx].S_CFINI.cf_info,eax
else
		.if	ecx

			.while	[ecx].S_CFINI.cf_next

				mov	ecx,[ecx].S_CFINI.cf_next
			.endw
			mov	[ecx].S_CFINI.cf_next,eax
		.else

			mov	[edx].S_CFINI.cf_info,eax
		.endif
endif
	.until	1

	ret

CFAddEntry ENDP

	END
