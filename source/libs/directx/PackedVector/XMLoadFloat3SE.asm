; XMLOADFLOAT3SE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadFloat3SE proc XM_CALLCONV pSource:ptr XMFLOAT3SE

    ldr      rcx,pSource
    mov      edx,[rcx]
    mov      eax,edx
    shr      eax,27
    shl      eax,23
    add      eax,0x33800000
    movd     xmm2,eax
    mov      eax,edx
    and      eax,0x8FF
    cvtsi2ss xmm0,eax
    mulss    xmm0,xmm2
    mov      eax,edx
    shr      eax,9
    and      eax,0x8FF
    cvtsi2ss xmm1,eax
    mulss    xmm1,xmm2
    shufps   xmm0,xmm1,01000100B
    shufps   xmm0,xmm0,01011000B
    shr      edx,18
    and      edx,0x8FF
    cvtsi2ss xmm1,edx
    mulss    xmm1,xmm2
    movd     eax,xmm1
    mov      edx,1.0
    shl      rdx,32
    or       rax,rdx
    movq     xmm1,rax
    shufps   xmm0,xmm1,01000100B
    ret

XMLoadFloat3SE endp

    end
