; _TOLOWER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include tchar.inc

    .code

_totlower proc c:int_t

    ldr eax,c
    .if ( eax >= 'A' && eax <= 'Z' )
        add eax,'a' - 'A'
    .endif
    ret

_totlower endp

    end
