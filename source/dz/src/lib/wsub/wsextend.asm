include alloc.inc
include string.inc
include wsub.inc

	.code

	ASSUME	esi: ptr S_WSUB

wsextend PROC USES esi edi ebx wsub:PTR S_WSUB

	mov esi,wsub
	mov edi,[esi].ws_maxfb
	add edi,edi
	.if malloc(addr [edi*4])
	    mov ebx,eax
	    memcpy(ebx, [esi].ws_fcb, addr [edi*2])
	    free([esi].ws_fcb)
	    mov [esi].ws_fcb,ebx
	    mov [esi].ws_maxfb,edi
	    mov eax,edi
	.endif
	ret

wsextend ENDP

	END
