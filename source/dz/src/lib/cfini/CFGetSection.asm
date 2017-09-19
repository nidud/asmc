include cfini.inc
include string.inc

    .code

CFGetSection proc __section:LPSTR

    mov eax,__CFBase
    .if eax

        __CFGetSection(eax, __section)
    .endif
    ret

CFGetSection endp

    END
