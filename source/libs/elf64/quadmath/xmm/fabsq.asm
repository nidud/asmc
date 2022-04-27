; FABSQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

    .code

    option win64:noauto

fabsq proc Q:real16

    andps xmm0,{ 7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFr }
    ret

fabsq endp

    end
