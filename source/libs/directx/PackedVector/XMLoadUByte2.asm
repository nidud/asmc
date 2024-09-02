; XMLOADUBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUByte2 proc XM_CALLCONV pSource:ptr XMUBYTE2

    ldr      rcx,pSource
    movzx    eax,[rcx].XMUBYTE2.x
    cvtsi2ss xmm0,eax
    movzx    eax,[rcx].XMUBYTE2.y
    cvtsi2ss xmm1,eax
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B
    ret

XMLoadUByte2 endp

    end
