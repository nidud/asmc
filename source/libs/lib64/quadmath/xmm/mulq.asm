; MULQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

mulq proc vectorcall dest:real16, src:real16

    __mulq(&dest, &src)
    ret

mulq endp

    end
