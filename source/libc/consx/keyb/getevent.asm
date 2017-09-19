include consx.inc

    .code

getevent proc

    .while !getkey()

        .break .if tdidle()

        mov eax,keyshift
        mov eax,[eax]
        .if eax & SHIFT_MOUSEFLAGS
            .if mousep()
                mov eax,MOUSECMD
                .break
            .endif
        .endif
    .endw
    ret

getevent endp

    END
