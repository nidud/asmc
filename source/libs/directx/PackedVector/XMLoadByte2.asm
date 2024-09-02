; XMLOADBYTE2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadByte2 proc XM_CALLCONV pSource:ptr XMBYTE2

    ldr      rcx,pSource

    movsx    eax,[rcx].XMBYTE2.x
    movsx    edx,[rcx].XMBYTE2.y
    cvtsi2ss xmm0,eax
    cvtsi2ss xmm1,edx
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B
    ret

XMLoadByte2 endp

    end
