include consx.inc

    .code

rcopen proc rect:dword, flag:dword, attrib:dword, ttl:LPSTR, wp:LPWSTR

    .repeat

        .if !(flag & _D_MYBUF)

            mov wp,rcalloc(rect, flag)
            .break .if !eax
        .endif

        rcread(rect, wp)
        mov edx,flag
        and edx,_D_CLEAR or _D_BACKG or _D_FOREG
        .break .ifz

        movzx eax,rect.S_RECT.rc_row
        mul rect.S_RECT.rc_col
        mov ecx,attrib

        .switch edx
          .case _D_CLEAR : wcputw (wp, eax, ' ') : .endc
          .case _D_COLOR : wcputa (wp, eax, ecx) : .endc
          .case _D_BACKG : wcputbg(wp, eax, ecx) : .endc
          .case _D_FOREG : wcputfg(wp, eax, ecx) : .endc
          .default
            mov ch,cl
            mov cl,' '
            wcputw(wp, eax, ecx)
        .endsw

        xor eax,eax
        .if eax != ttl

            mov al,rect.S_RECT.rc_col
            wctitle(wp, eax, ttl)
        .endif

    .until 1
    mov eax,wp
    test eax,eax
    ret

rcopen endp

    END
