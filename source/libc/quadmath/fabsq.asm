; FABSQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include quadmath.inc

    .code

fabsq proc Q:real16
ifdef _WIN64
    mov     rax,0x7FFFFFFFFFFFFFFF
    movq    xmm1,rax
    shufps  xmm1,xmm1,01000000B
    andps   xmm0,xmm1
endif
    ret
fabsq endp

    end
