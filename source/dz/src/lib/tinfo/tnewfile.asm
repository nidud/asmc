include tinfo.inc

    .code

tnewfile proc uses esi

    mov esi,tinfo
    .if topen(0, 0)

        titogglefile(esi, eax)
        mov tinfo,eax
    .endif
    ret

tnewfile endp

    END
