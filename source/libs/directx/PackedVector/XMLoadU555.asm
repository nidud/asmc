; XMLOADU555.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadU555 proc XM_CALLCONV pSource:ptr XMU555

    ldr     rcx,pSource
    movzx   edx,[rcx].XMU555.v
    mov     eax,edx
    and     eax,0x1F
    cvtsi2ss xmm0,eax
    mov     eax,edx
    shr     eax,5
    and     eax,0x1F
    cvtsi2ss xmm1,eax
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B
    mov     eax,edx
    shr     eax,10
    and     eax,0x1F
    cvtsi2ss xmm1,eax
    shr     edx,15
    and     edx,0x1
    cvtsi2ss xmm2,edx
    shufps  xmm1,xmm2,01000100B
    shufps  xmm1,xmm1,01011000B
    shufps  xmm0,xmm1,01000100B
    ret

XMLoadU555 endp

    end
