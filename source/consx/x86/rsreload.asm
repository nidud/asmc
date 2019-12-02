; RSRELOAD.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

rsreload proc uses ebx robj:ptr S_ROBJ, dobj:ptr S_DOBJ

    mov ebx,dobj
    mov eax,[ebx]
    and eax,_D_DOPEN
    .ifnz
        dlhide(dobj)

        push  eax
        movzx eax,[ebx].S_DOBJ.dl_count
        inc   eax
        lea   eax,[eax*8+2]
        add   eax,robj
        mov   ecx,eax
        mov   al,[ebx].S_DOBJ.dl_rect.rc_col
        mul   [ebx].S_DOBJ.dl_rect.rc_row

        .if [ebx].S_DOBJ.dl_flag & _D_RESAT
            or eax,8000h
        .endif
        xchg ecx,eax
        wcunzip([ebx].S_DOBJ.dl_wp, eax, ecx)
        dlinit(dobj)
        pop eax
        .if eax
            dlshow(dobj)
        .endif
    .endif
    ret

rsreload endp

    END
