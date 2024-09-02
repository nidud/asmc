; XMVECTORGETXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetXPtr proc XM_CALLCONV x:ptr float, V:FXMVECTOR

    ldr rcx,x
    ldr xmm1,V

    _mm_store_ss([rcx], xmm1)
    ret

XMVectorGetXPtr endp

    end
