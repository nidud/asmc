; XMLOADUDECN4_XR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUDecN4_XR proc XM_CALLCONV pSource:ptr XMUDECN4

    ldr     rcx,pSource
    mov     edx,[rcx].XMUDECN4.v
    mov     eax,edx
    and     eax,0x3FF
    sub     eax,0x180
    cvtsi2ss xmm0,eax
    mov     eax,510.0
    movd    xmm2,eax
    divss   xmm0,xmm2

    mov     eax,edx
    shr     eax,10
    and     eax,0x3FF
    sub     eax,0x180
    cvtsi2ss xmm1,eax
    divss   xmm1,xmm2
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B

    mov     eax,edx
    shr     eax,20
    and     eax,0x3FF
    sub     eax,0x180
    cvtsi2ss xmm1,eax
    divss   xmm1,xmm2

    shr     edx,30
    cvtsi2ss xmm2,edx
    mov     eax,3.0
    movd    xmm3,eax
    divss   xmm2,xmm3
    shufps  xmm1,xmm2,01000100B
    shufps  xmm1,xmm1,01011000B
    shufps  xmm0,xmm1,01000100B
    ret

XMLoadUDecN4_XR endp

    end
