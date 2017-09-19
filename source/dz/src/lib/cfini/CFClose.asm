include cfini.inc

    .code

CFClose proc

    mov eax,__CFBase
    .if eax

        __CFClose(eax)
        mov __CFBase,0
    .endif
    ret

CFClose endp

    END
