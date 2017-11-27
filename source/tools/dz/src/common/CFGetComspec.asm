include cfini.inc

    .code

CFGetComspec proc value:UINT

    mov eax,__CFBase
    .if eax

        __CFGetComspec(eax, value)
    .endif
    ret

CFGetComspec endp

    END
