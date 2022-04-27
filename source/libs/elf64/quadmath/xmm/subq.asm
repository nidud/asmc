; SUBQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

subq proc dest:real16, src:real16

    .new a:real16 = xmm0
    .new b:real16 = xmm1
    __subq(&a, &b)
    ret

subq endp

    end
