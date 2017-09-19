include direct.inc

    .code

_wgetcwd proc buffer:LPWSTR, maxlen:SINT

    _wgetdcwd(0, buffer, maxlen)
    ret

_wgetcwd endp

    END
