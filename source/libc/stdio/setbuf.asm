include stdio.inc

    .code

setbuf proc fp:LPFILE, buf:LPSTR

    setvbuf(buf, fp, _IOFBF, _MINIOBUF)
    ret

setbuf endp

    END
