include tinfo.inc

    .code

tclosefile proc
    .if tclose()
        push eax
        tishow(eax)
        pop eax
        mov tinfo,eax
        xor eax,eax
    .else
        mov eax,_TI_RETEVENT
    .endif
    ret
tclosefile endp

    END
