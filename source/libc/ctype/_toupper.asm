; _TOUPPER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include ctype.inc
include tchar.inc

    .code

_totupper proc c:int_t

    ldr eax,c
    .if ( eax >= 'a' && eax <= 'z' )
        sub eax,'a' - 'A'
    .endif
    ret

_totupper endp

    end
