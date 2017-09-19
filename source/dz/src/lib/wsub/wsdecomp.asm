include wsub.inc
include errno.inc

    .code

wsdecomp proc wsub, fblk, out_path
    mov eax,fblk
    .if !([eax].S_FBLK.fb_flag & _FB_ARCHIVE)
        notsup()
        or eax,-1
    .else
        wzipcopy(wsub, fblk, out_path)
    .endif
    ret
wsdecomp endp

    END
