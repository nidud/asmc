include cfini.inc

    .code

CFGetSectionID proc section:LPSTR, id:UINT

    mov eax,__CFBase
    .if eax

        .if INIGetSection(eax, section)

            INIGetEntryID(eax, id)
        .endif
    .endif
    ret

CFGetSectionID endp

    END
