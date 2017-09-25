include cfini.inc

    .code

CFWrite proc file:LPSTR

    mov eax,__CFBase
    .if eax

        INIWrite(eax, file)
    .endif
    ret

CFWrite endp

    END
