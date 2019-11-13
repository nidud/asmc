; FABSQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

fabsq proc vectorcall Q:real16

    andps xmm0,FLTQ(0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF)
    ret

fabsq endp

    end
