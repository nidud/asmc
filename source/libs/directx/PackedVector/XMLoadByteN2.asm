; XMLOADBYTEN2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMLoadByteN2 proc XM_CALLCONV pSource:ptr XMBYTEN2

    ldr rcx,pSource

    movsx eax,[rcx].XMBYTEN2.x
    movd  xmm0,-1.0

    .if ( al != -128 )

        cvtsi2ss xmm0,eax
        mulss xmm0,1.0/127.0
    .endif
    movsx eax,[rcx].XMBYTEN2.y
    movd  xmm1,-1.0
    .if ( al != -128 )

        cvtsi2ss xmm1,eax
        mulss xmm1,1.0/127.0
    .endif
    shufps xmm0,xmm1,01000100B
    shufps xmm0,xmm0,01011000B
    ret

XMLoadByteN2 endp

    end
