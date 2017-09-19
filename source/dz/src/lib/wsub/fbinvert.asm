include wsub.inc

    .code

fbinvert proc fblk:ptr S_FBLK

    mov eax,fblk
    .if ![eax].S_FBLK.fb_flag & _FB_UPDIR

        xor [eax].S_FBLK.fb_flag,_FB_SELECTED
    .else

        xor eax,eax
    .endif
    ret

fbinvert endp

    END
