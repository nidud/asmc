include cfini.inc

    .code

CFAddSection proc __section:LPSTR

    mov eax,__CFBase
    .if eax

        INIAddSection(eax, __section)
    .endif
    ret

CFAddSection endp

    END
