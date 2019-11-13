; FMINQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:rsp nosave noauto

fminq proc vectorcall A:real16, B:real16

    .ifd cmpq(xmm0, xmm1) == 1

        movaps xmm0,xmm1
    .endif
    ret

fminq endp

    end
