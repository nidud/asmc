include iost.inc
include io.inc

    .code

ioclose proc uses eax io:ptr S_IOST
    mov eax,io
    _close([eax].S_IOST.ios_file)
    iofree(io)
    ret
ioclose endp

    END
