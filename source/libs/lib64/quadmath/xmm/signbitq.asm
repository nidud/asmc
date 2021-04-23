; SIGNBITQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

signbitq proc vectorcall V:real16

    shufpd  xmm0,xmm0,1
    movq    rax,xmm0
    shufpd  xmm0,xmm0,1
    shr     rax,63
    ret

signbitq endp

    end
