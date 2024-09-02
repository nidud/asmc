; XMLOADHALF2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadHalf2 proc XM_CALLCONV pSource:ptr XMHALF2

    ldr     rcx,pSource
    movzx   eax,[rcx].XMHALF2.x
    movzx   edx,[rcx].XMHALF2.y
    movd    xmm0,edx
    movd    xmm2,eax
    XMConvertHalfToFloat(xmm0)
    movaps  xmm1,xmm0
    XMConvertHalfToFloat(xmm2)
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B
    ret

XMLoadHalf2 endp

    end
