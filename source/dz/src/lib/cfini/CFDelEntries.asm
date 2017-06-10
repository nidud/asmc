include alloc.inc
include cfini.inc

	.code

CFDelEntries PROC USES esi __ini:PCFINI

	mov eax,__ini
	mov esi,[eax].S_CFINI.cf_info
	mov [eax].S_CFINI.cf_info,0

	.while esi

		.if [esi].S_CFINI.cf_name

			free([esi].S_CFINI.cf_name)
		.endif

		mov eax,esi
		mov esi,[esi].S_CFINI.cf_next
		free(eax)
	.endw
	mov eax,__ini
	ret

CFDelEntries ENDP

	END
