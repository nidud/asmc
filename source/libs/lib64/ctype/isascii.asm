; ISASCII.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isascii proc c:int_t

    mov     eax,ecx
    and     eax,0x80
    setz    al
    ret

isascii endp

    end

