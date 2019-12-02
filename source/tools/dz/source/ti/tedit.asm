include tinfo.inc

    .code

tedit proc fname:LPSTR, line

    .if topen(fname, 0)

        tialigny(tinfo, line)
        tmodal()
    .endif
    ret

tedit endp

    END
