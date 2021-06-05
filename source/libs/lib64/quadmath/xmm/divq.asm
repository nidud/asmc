; DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

divq proc vectorcall dest:real16, src:real16

    __divq(&dest, &src)
    ret

divq endp

    end
