; SIGNBITQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

signbitq proc q:real16
ifdef _WIN64
    shufpd  xmm0,xmm0,1
    movq    rax,xmm0
    shufpd  xmm0,xmm0,1
    shr     rax,63
endif
    ret
signbitq endp

    end
