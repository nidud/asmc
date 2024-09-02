; XMLOADU565.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadU565 proc XM_CALLCONV pSource:ptr XMU565

    ldr      rcx,pSource
    movzx    eax,[rcx].XMU565.v
    mov      edx,eax
    and      eax,0x1F
    cvtsi2ss xmm0,eax
    mov      eax,edx
    shr      eax,5
    and      eax,0x3F
    cvtsi2ss xmm1,eax
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B
    shr      edx,11
    and      edx,0x1F
    cvtsi2ss xmm1,edx
    shufps   xmm0,xmm1,01000100B
    ret

XMLoadU565 endp

    end
