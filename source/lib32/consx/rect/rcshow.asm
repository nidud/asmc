include consx.inc

    .code

rcshow proc rect, flag, wp:PVOID

    .repeat

        mov eax,flag
        and eax,_D_DOPEN or _D_ONSCR
        .break .ifz

        and eax,_D_ONSCR
        .ifz

            .break .if !rcxchg(rect, wp)

            .if byte ptr flag & _D_SHADE

                rcsetshade(rect, wp)
            .endif
        .endif
        xor eax,eax
        inc eax
    .until 1
    ret

rcshow endp

    END
