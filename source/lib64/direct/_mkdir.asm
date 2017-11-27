include io.inc
include direct.inc
include winbase.inc

    .code

    option win64:nosave rsp

_mkdir proc directory:LPSTR

    .if !CreateDirectoryA(rcx, 0)

        osmaperr()
    .else
        xor eax,eax
    .endif
    ret

_mkdir endp

    END
