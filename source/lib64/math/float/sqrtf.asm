; SQRTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc

    .code

    option win64:rsp nosave noauto

sqrtf proc x:float

    sqrtss xmm0,xmm0
    ret

sqrtf endp

    end
