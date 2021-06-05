; SUBQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

subq proc vectorcall dest:real16, src:real16

    __subq(&dest, &src)
    ret

subq endp

    end
