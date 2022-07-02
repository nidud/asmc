; ROUNDF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include math.inc
include intrin.inc

    .code

roundf proc f:float
ifdef __SSE__
    movd    eax,xmm0
    shl     eax,1
    sbb     edx,edx
    shr     eax,1
    movd    xmm0,eax
    cvtss2si eax,xmm0
    cvtsi2ss xmm1,eax
    subss   xmm0,xmm1
    .if _mm_comige_ss(xmm0, 0.5)
        inc eax
    .endif
    .if edx
        neg eax
    .endif
    cvtsi2ss xmm0,eax
else
    int 3
endif
    ret

roundf endp

    end
