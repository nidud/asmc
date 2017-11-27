include consx.inc

    .code

    assume edx:ptr S_DOBJ

dlhide proc dobj:ptr S_DOBJ

    mov edx,dobj
    .if rchide([edx].dl_rect, [edx].dl_flag, [edx].dl_wp)

        mov edx,dobj
        and [edx].dl_flag,not _D_ONSCR
    .endif
    ret

dlhide endp

    END
