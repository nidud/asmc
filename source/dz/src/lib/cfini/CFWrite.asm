include cfini.inc

    .code

CFWrite proc __file:LPSTR

    mov eax,__CFBase
    .if eax

        __CFWrite(eax, __file)
    .endif
    ret

CFWrite endp

    END
