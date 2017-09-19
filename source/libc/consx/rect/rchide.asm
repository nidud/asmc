include consx.inc

    .code

rchide proc rect, fl, wp:PVOID

    .repeat
        mov eax,fl
        and eax,_D_DOPEN or _D_ONSCR
        .break .ifz

        .if eax & _D_ONSCR

            .break .if !rcxchg(rect, wp)

            .if fl & _D_SHADE

                rcclrshade(rect, wp)
            .endif
        .endif
        xor eax,eax
        inc eax
    .until 1
    ret

rchide endp

    END
