include direct.inc
include string.inc
include alloc.inc

	.code

recursive PROC USES esi edi fname:LPSTR, src:LPSTR, dst:LPSTR
	alloca( WMAXPATH * 2 )
	mov	esi,eax
	lea	edi,[eax+WMAXPATH]
	strfcat(esi, src, fname)
	strcpy (edi, dst)
	strfcat(edi, edi, strfn(esi))
	strlen (esi)
	mov	WORD PTR [esi+eax],005Ch
	inc	eax
	.if	_strnicmp( esi, edi, eax )
		mov	eax,-1
	.endif
	inc	eax
	mov	esp,ebp
	ret
recursive ENDP

	END
