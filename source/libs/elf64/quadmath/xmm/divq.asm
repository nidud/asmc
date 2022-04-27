; DIVQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

divq proc dest:real16, src:real16

    .new a:real16 = xmm0
    .new b:real16 = xmm1
    __divq(&a, &b)
    ret

divq endp

    end
