include io.inc
include direct.inc
include winbase.inc

    .code

    option win64:nosave rsp

_rmdirw proc directory:LPWSTR

    .if RemoveDirectoryW(rcx)
        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_rmdirw endp

    END
