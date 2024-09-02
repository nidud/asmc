; XMVECTORGETINTXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetIntXPtr proc XM_CALLCONV p:ptr uint32_t, V:FXMVECTOR

    ldr rcx,p
    ldr xmm1,V

    _mm_store_ss([rcx], xmm1)
    ret

XMVectorGetIntXPtr endp

    end
