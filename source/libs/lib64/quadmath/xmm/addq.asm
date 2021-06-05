; ADDQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

addq proc vectorcall dest:real16, src:real16

    __addq(&dest, &src)
    ret

addq endp

    end
