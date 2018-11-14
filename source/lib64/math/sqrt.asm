; SQRT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;


include math.inc

    .code

    option win64:rsp nosave noauto

sqrt proc x:double

    sqrtpd xmm0,xmm0
    ret

sqrt endp

    end
