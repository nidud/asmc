include cfini.inc

    .code

CFGetEntryID proc ini:PCFINI, entry:UINT

    mov eax,entry ; 0..99
    .while  al > 9
        add ah,1
        sub al,10
    .endw
    .if ah
        xchg    al,ah
        or  ah,'0'
    .endif
    or  al,'0'
    mov entry,eax

    CFGetEntry(ini, addr entry)
    ret

CFGetEntryID endp

    END
