include alloc.inc
include cfini.inc

    .code

    assume esi:ptr S_CFINI
    assume edi:ptr S_CFINI

__CFClose proc uses esi edi ebx __ini:PCFINI

    mov esi,__ini

    .while esi

	.if [esi].cf_name

	    free([esi].cf_name)
	.endif

	mov edi,[esi].cf_info
	.while	edi

	    .if [edi].cf_name

		free([edi].cf_name)
	    .endif

	    mov eax,edi
	    mov edi,[edi].cf_next
	    free  (eax)
	.endw

	mov eax,esi
	mov esi,[esi].cf_next
	free  (eax)
    .endw
    ret

__CFClose endp

    END
