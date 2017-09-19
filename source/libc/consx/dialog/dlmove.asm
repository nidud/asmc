include consx.inc

    .code

dlmove proc dobj:ptr S_DOBJ

    xor eax,eax
    mov edx,dobj
    mov cx,[edx]
    and ecx,_D_DMOVE or _D_DOPEN or _D_ONSCR

    .repeat

        .break .if ecx != _D_DMOVE or _D_DOPEN or _D_ONSCR
        .break .if !mousep()

        mov edx,dobj
        lea eax,[edx].S_DOBJ.dl_rect
        movzx ecx,[edx].S_DOBJ.dl_flag
        rcmsmove(eax, [edx].S_DOBJ.dl_wp, ecx)
        mov eax,1
    .until 1
    ret

dlmove endp

    END
