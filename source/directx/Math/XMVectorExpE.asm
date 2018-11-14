; XMVECTOREXPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorExpE proc XM_CALLCONV V:FXMVECTOR

    _mm_store_ps(V, xmm6)
    _mm_store_ps(V[16], xmm7)

    inl_XMVectorExpE(xmm0)

    _mm_store_ps(xmm6, V)
    _mm_store_ps(xmm7, V[16])
    ret
XMVectorExpE endp

    end
