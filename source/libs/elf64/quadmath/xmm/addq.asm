; ADDQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

addq proc dest:real16, src:real16

    .new a:real16 = xmm0
    .new b:real16 = xmm1
    __addq(&a, &b)
    ret

addq endp

    end
