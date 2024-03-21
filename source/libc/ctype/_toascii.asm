; _TOASCII.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include tchar.inc

    .code

_totascii proc c:int_t

    ldr eax,c
    and eax,0x7F
    ret

_totascii endp

    end

