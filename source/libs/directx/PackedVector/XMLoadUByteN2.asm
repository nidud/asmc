; XMLOADUBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUByteN2 proc XM_CALLCONV pSource:ptr XMUBYTEN2

    ldr      rcx,pSource
    movzx    eax,[rcx].XMUBYTEN2.x
    cvtsi2ss xmm0,eax
    mulss    xmm0,1.0/255.0
    movzx    eax,[rcx].XMUBYTEN2.y
    cvtsi2ss xmm1,eax
    mulss    xmm1,1.0/255.0
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B
    ret

XMLoadUByteN2 endp

    end
