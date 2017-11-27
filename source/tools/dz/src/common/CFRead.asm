include cfini.inc

    .code

CFRead proc file:LPSTR

    mov __CFBase,INIRead(__CFBase, file)
    ret

CFRead endp

    END
