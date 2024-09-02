; XMLOADUNIBBLE4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadUNibble4 proc XM_CALLCONV pSource:ptr XMUNIBBLE4

    ldr     rcx,pSource
    movzx   edx,[rcx].XMUNIBBLE4.v
    mov     eax,edx
    and     eax,0xF
    cvtsi2ss xmm0,eax
    mov     eax,edx
    shr     eax,4
    and     eax,0xF
    cvtsi2ss xmm1,eax
    shufps  xmm0,xmm1,01000100B
    shufps  xmm0,xmm0,01011000B
    mov     eax,edx
    shr     eax,8
    and     eax,0xF
    cvtsi2ss xmm1,eax
    shr     edx,12
    and     edx,0xF
    cvtsi2ss xmm2,edx
    shufps  xmm1,xmm2,01000100B
    shufps  xmm1,xmm1,01011000B
    shufps  xmm0,xmm1,01000100B
    ret

XMLoadUNibble4 endp

    end
