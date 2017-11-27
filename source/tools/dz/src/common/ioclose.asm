include iost.inc
include io.inc

    .code

ioclose proc uses eax io:ptr S_IOST
    mov eax,io
    mov eax,[eax].S_IOST.ios_file
    .if eax != -1
        _close(eax)
    .endif
    iofree(io)
    ret
ioclose endp

    END
