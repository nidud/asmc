include cfini.inc

    .code

CFRead proc __file:LPSTR

    mov __CFBase,__CFRead(__CFBase, __file)
    ret

CFRead endp

    END
