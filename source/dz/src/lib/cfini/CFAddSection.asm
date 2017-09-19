include cfini.inc

    .code

CFAddSection proc __section:LPSTR

    mov eax,__CFBase
    .if eax

        __CFAddSection(eax, __section)
    .endif
    ret

CFAddSection endp

    END
