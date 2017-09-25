include cfini.inc
include string.inc

    .code

CFGetSection proc section:LPSTR

    mov eax,__CFBase
    .if eax

        INIGetSection(eax, section)
    .endif
    ret

CFGetSection endp

    END
