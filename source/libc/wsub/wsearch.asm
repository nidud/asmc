include string.inc
include wsub.inc

	.code

wsearch PROC USES esi edi wsub:PTR S_WSUB, string:LPSTR
	mov	eax,wsub
	mov	esi,[eax].S_WSUB.ws_count
	mov	edi,[eax].S_WSUB.ws_fcb
@@:
	mov	eax,-1
	test	esi,esi
	jz	@F
	dec	esi
	mov	eax,[edi]
	add	eax,S_FBLK.fb_name
	add	edi,4
	_stricmp( string, eax )
	jne	@B
	mov	eax,wsub
	mov	eax,[eax].S_WSUB.ws_count
	sub	eax,esi
	dec	eax
@@:
	ret
wsearch ENDP

	END
