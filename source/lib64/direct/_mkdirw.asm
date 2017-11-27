include io.inc
include direct.inc
include winbase.inc

    .code

    option win64:nosave rsp

_mkdirw proc directory:LPWSTR

    .if CreateDirectoryW(rcx, 0)
        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_mkdirw endp

    END
