; ISASCII.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isascii proc c:int_t

    test    dil,0x80
    setz    al
    movzx   eax,al
    ret

isascii endp

    end

