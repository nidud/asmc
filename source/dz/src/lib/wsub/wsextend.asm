include alloc.inc
include string.inc
include wsub.inc

    .code

    assume esi:ptr S_WSUB

wsextend proc uses esi edi ebx wsub:ptr S_WSUB

    mov esi,wsub
    mov edi,[esi].ws_maxfb
    add edi,edi
    .if malloc(&[edi*4])
	mov ebx,eax
	memcpy(ebx, [esi].ws_fcb, &[edi*2])
	free([esi].ws_fcb)
	mov [esi].ws_fcb,ebx
	mov [esi].ws_maxfb,edi
	mov eax,edi
    .endif
    ret

wsextend endp

    END
