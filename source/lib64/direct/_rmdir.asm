include io.inc
include direct.inc
include winbase.inc

    .code

    option win64:nosave rsp

_rmdir proc directory:LPSTR

    .if RemoveDirectoryA(rcx)
        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_rmdir endp

    END
