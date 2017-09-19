include stdlib.inc

    .code

_wtoi proc string:LPWSTR

    _wtol(string)
    ret

_wtoi endp

    END
