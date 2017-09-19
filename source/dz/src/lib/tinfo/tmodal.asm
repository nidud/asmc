include tinfo.inc

    .data

tiupdate_line dd -1
tiupdate_offs dd -1

    .code

    assume esi:ptr S_TINFO

tiupdate proc private uses esi

    mov esi,tinfo
    .if tistate(esi)

        .if edx & _D_ONSCR && ecx & _T_USEMENUS

            mov eax,[esi].ti_loff
            add eax,[esi].ti_yoff
            mov edx,[esi].ti_xoff
            add edx,[esi].ti_boff

            .if eax != tiupdate_line || edx != tiupdate_offs

                mov tiupdate_offs,edx
                mov tiupdate_line,eax

                timenus(esi)
            .endif
        .endif
    .endif
    xor eax,eax
    ret
tiupdate endp

tmodal proc uses esi edi ebx

    local cursor:S_CURSOR, update, ftime

    .while mousep()
    .endw

    mov esi,tinfo
    .if tistate(esi)

        mov eax,tupdate
        mov update,eax
        mov tupdate,tiupdate
        CursorGet(&cursor)
        tishow(esi)

        mov ftime,tiftime(esi)
        mov edi,tevent()
        mov eax,tinfo
        cmp eax,esi
        mov esi,0

        .ifz

            tiftime(eax)
            mov esi,ftime
            sub esi,eax
        .endif

        mov eax,update
        mov tupdate,eax
        CursorSet(&cursor)

        mov edx,esi     ; zero if not modified
        mov eax,edi     ; returned key value
        test eax,eax
    .endif
    ret

tmodal endp

    END
