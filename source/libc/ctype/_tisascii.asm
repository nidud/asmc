; _TISASCII.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc
include tchar.inc

    .code

_istascii proc c:int_t

    ldr     eax,c
    test    eax,0xFFFFFF80
    setz    al
    movzx   eax,al
    ret

_istascii endp

    end

