include alloc.inc
include wsub.inc

    .code

wsfree proc uses esi edi wsub:ptr S_WSUB

    xor eax,eax
    mov ecx,wsub
    mov edi,[ecx].S_WSUB.ws_count
    mov [ecx].S_WSUB.ws_count,eax
    mov esi,[ecx].S_WSUB.ws_fcb

    .if esi

	push edi
	.while edi

	    free([esi])
	    mov [esi],eax
	    add esi,4
	    dec edi
	.endw
	pop eax
    .endif
    ret

wsfree endp

    END
