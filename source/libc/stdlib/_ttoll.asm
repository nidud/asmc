; _TTOLL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

    .code

_ttoll proc string:tstring_t

    _ttoi64( ldr(string) )
    ret

_ttoll endp

    end
