include direct.inc
include errno.inc
include winbase.inc

    .code

    option win64:nosave

_wrmdir proc directory:LPWSTR

    .if RemoveDirectoryW(rcx)
        xor eax,eax
    .else
        osmaperr()
    .endif
    ret

_wrmdir endp

    END
