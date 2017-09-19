include tinfo.inc

    .code

    assume edx:ptr S_TINFO

tnextfile proc

    .if tigetfile(tinfo)

        .if ecx > 1

            mov edx,tinfo
            .if [edx].ti_next

                mov eax,[edx].ti_next
            .endif

            titogglefile(edx, eax)
        .endif

        mov tinfo,eax
    .endif
    ret

tnextfile endp

    END
