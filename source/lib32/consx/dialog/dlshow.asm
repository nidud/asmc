include consx.inc

    .code

    assume edi: ptr S_DOBJ

dlshow proc uses edi dobj:ptr S_DOBJ
    mov edi,dobj
    .if rcshow([edi].dl_rect, [edi].dl_flag, [edi].dl_wp)
        or [edi].dl_flag,_D_ONSCR
    .endif
    ret
dlshow endp

    END
