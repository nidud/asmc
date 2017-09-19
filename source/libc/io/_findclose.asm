include errno.inc
include winbase.inc

    .code

_findclose proc h:HANDLE

    .if !FindClose(h)

        osmaperr()
    .else
        xor eax,eax
    .endif
    ret

_findclose endp

    END
