include cfini.inc

    .code

CFExpandCmd proc buffer:LPSTR, file:LPSTR, section:LPSTR

    mov eax,__CFBase
    .if eax

        .if INIGetSection(eax, section)

            __CFExpandCmd(eax, buffer, file)
        .endif
    .endif
    ret

CFExpandCmd endp

    END
