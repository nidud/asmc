; COSQ.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include quadmath.inc

ifdef __SSE__
    .data
    cosoffs real16 0.0, -M_PI/2.0, 0.0, -M_PI/2.0
    cossign real16 1.0, -1.0, -1.0, 1.0, -0.0, -0.0
endif

    .code

ifdef __SSE__

common proc private uses rsi
    and  ecx,3
    imul esi,ecx,16
    subq(xmm2, mulq(cvtsiq(rdx::rax), 1.5707963267948966))
    lea rax,cosoffs
    mulq(addq(xmm0, [rax+rsi]), xmm0)
    lea rax,cossign
    xorps xmm0,[rax+4*16]
    movaps xmm2,xmm0
    addq(mulq(xmm0, 1.5619206968586225e-016), 4.7794773323873853e-014)
    addq(mulq(xmm0, xmm2), 1.1470745597729725e-011)
    addq(mulq(xmm0, xmm2), 2.0876756987868100e-009)
    addq(mulq(xmm0, xmm2), 2.7557319223985888e-007)
    addq(mulq(xmm0, xmm2), 2.4801587301587302e-005)
    addq(mulq(xmm0, xmm2), 1.3888888888888889e-003)
    addq(mulq(xmm0, xmm2), 4.1666666666666664e-002)
    addq(mulq(xmm0, xmm2), 0.5)
    addq(mulq(xmm0, xmm2), 1.0)
    lea rax,cossign
    mulq(xmm0, [rax+rsi])
    ret
common endp

endif

cosq proc q:real16
ifdef _WIN64
    movaps  xmm2,xmm0
    mulq   ( xmm0, 0.63661977236758138 )
    cvttqsi( xmm0 )
    mov     ecx,eax
    call    common
else
    int     3
endif
    ret
cosq endp

sinq proc x:real16
ifdef _WIN64
    movaps  xmm2,xmm0
    mulq   ( xmm0, 0.63661977236758138 )
    cvttqsi( xmm0 )
    lea     ecx,[rax-1]
    call    common
else
    int     3
endif
    ret
sinq endp

    end
