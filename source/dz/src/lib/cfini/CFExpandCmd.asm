include cfini.inc

    .code

CFExpandCmd proc buffer:LPSTR, __file:LPSTR, __section:LPSTR

    mov eax,__CFBase
    .if eax

        .if __CFGetSection(eax, __section)

            __CFExpandCmd(eax, buffer, __file)
        .endif
    .endif
    ret

CFExpandCmd endp

    END
