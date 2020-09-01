; _WTOI.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

    .code

_wtoi proc string:LPWSTR

    _wtol(string)
    ret

_wtoi endp

    END
