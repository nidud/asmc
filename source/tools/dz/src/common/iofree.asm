include iost.inc
include malloc.inc

    .code

iofree proc uses eax edx io:ptr S_IOST

    xor	 eax,eax
    mov	 ecx,io
    push [ecx].S_IOST.ios_bp
    mov	 [ecx].S_IOST.ios_bp,eax
    pop	 eax
    free(eax)
    ret

iofree endp

    END
