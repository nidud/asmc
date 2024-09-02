; XMLOADHALF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadHalf4 proc XM_CALLCONV pSource:ptr XMHALF4

    ldr     rcx,pSource

    movzx   eax,[rcx].XMHALF4.x
    movd    xmm1,eax
    movzx   eax,[rcx].XMHALF4.y
    movd    xmm2,eax
    movzx   eax,[rcx].XMHALF4.z
    movd    xmm3,eax
    movzx   eax,[rcx].XMHALF4.w
    movd    xmm4,eax

    movss   xmm2,XMConvertHalfToFloat(xmm2)
    movss   xmm3,XMConvertHalfToFloat(xmm3)
    movss   xmm4,XMConvertHalfToFloat(xmm4)
    XMConvertHalfToFloat(xmm1)

    shufps  xmm0,xmm2,01000100B
    shufps  xmm0,xmm0,01011000B
    shufps  xmm3,xmm4,01000100B
    shufps  xmm3,xmm3,01011000B
    shufps  xmm0,xmm3,01000100B
    ret

XMLoadHalf4 endp

    end
