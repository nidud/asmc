; COSHF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

coshf proc x:float

    cvtss2sd xmm0,xmm0
    cosh(xmm0)
    cvtsd2ss xmm0,xmm0
    ret

coshf endp

    end
