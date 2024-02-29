; _TTOLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ttoll proc string:LPTSTR

    ldr rcx,string
    _ttoi64(rcx)
    ret

_ttoll endp

    end
