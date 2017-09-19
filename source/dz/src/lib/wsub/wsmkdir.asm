include direct.inc
include wsub.inc

    .code

wsmkdir proc path:LPSTR

    .if _mkdir(path)
        ermkdir(path)
    .else
        inc eax
    .endif
    ret

wsmkdir endp

    END
