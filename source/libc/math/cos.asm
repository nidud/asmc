; COS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
define _USE_MATH_DEFINES

include math.inc

ifdef __SSE__
    .data
    cosoffs real8 0.0, -M_PI/2.0, 0.0, -M_PI/2.0
    cossign real8 1.0, -1.0, -1.0, 1.0, -0.0, -0.0
endif

.code

ifdef __SSE__
common proc private

    movaps  xmm2,xmm0
    xorps   xmm1,xmm1
    and     ecx,3
    cvtsi2sd xmm1,eax
    mulsd   xmm1,03ff921fb54442d18r
    subsd   xmm2,xmm1
    lea     rax,cosoffs
    addsd   xmm2,[rax+rcx*8]
    mulsd   xmm2,xmm2
    lea     rax,cossign
    xorps   xmm2,[rax+4*8]
    movaps  xmm0,xmm2
    mulsd   xmm0,03ca6827863b97d97r
    addsd   xmm0,03d2ae7f3e733b81fr
    mulsd   xmm0,xmm2
    addsd   xmm0,03da93974a8c07c9dr
    mulsd   xmm0,xmm2
    addsd   xmm0,03e21eed8eff8d898r
    mulsd   xmm0,xmm2
    addsd   xmm0,03e927e4fb7789f5cr
    mulsd   xmm0,xmm2
    addsd   xmm0,03efa01a01a01a01ar
    mulsd   xmm0,xmm2
    addsd   xmm0,03f56c16c16c16c17r
    mulsd   xmm0,xmm2
    addsd   xmm0,03fa5555555555555r
    mulsd   xmm0,xmm2
    addsd   xmm0,03fe0000000000000r
    mulsd   xmm0,xmm2
    addsd   xmm0,03ff0000000000000r
    mulsd   xmm0,[rax+rcx*8]
    ret
common endp
endif

cos proc x:double
ifdef __SSE__
    movaps  xmm1,xmm0
    mulsd   xmm1,03fe45f306dc9c883r
    cvttsd2si eax,xmm1
    mov     ecx,eax
    call    common
else
    fld   x
    fcos
endif
    ret
cos endp

sin proc x:double
ifdef __SSE__
    movaps  xmm1,xmm0
    mulsd   xmm1,03fe45f306dc9c883r
    cvttsd2si eax,xmm1
    lea     rcx,[rax-1]
    call    common
else
    fld     x
    fsin
endif
    ret
sin endp

    end
