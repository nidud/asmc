; COPYSIGNQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

copysignq proc number:real16, sign:real16
ifdef _WIN64
    mov     rax,0x7FFFFFFFFFFFFFFF
    movq    xmm2,rax
    shufps  xmm2,xmm2,01000000B
    andps   xmm0,xmm2
    andnps  xmm2,xmm1
    orps    xmm0,xmm2
endif
    ret
copysignq endp

    end
