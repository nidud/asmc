; ISASCII.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ctype.inc

    .code

isascii proc c:int_t
ifdef _WIN64
    test    cl,0x80
else
    test    byte ptr c,0x80
endif
    setz    al
    movzx   eax,al
    ret
isascii endp

    end

