; XMVECTORGETWPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorGetWPtr proc XM_CALLCONV w:ptr float, V:FXMVECTOR

    ldr rcx,w
    ldr xmm1,V

    XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(3,3,3,3))
    _mm_store_ss([rcx], xmm1)
    ret

XMVectorGetWPtr endp

    end
