include strlib.inc
include string.inc

    .code

    option win64:rsp

strmove proc dst:LPSTR, src:LPSTR

    memmove(dst, src, &[strlen(rdx)+1])
    ret

strmove endp

    END
