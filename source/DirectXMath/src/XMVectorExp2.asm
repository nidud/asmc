
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorExp proc XM_CALLCONV V:FXMVECTOR
XMVectorExp endp

XMVectorExp2 proc XM_CALLCONV V:FXMVECTOR
if _XM_VECTORCALL_ eq 0
    _mm_storeu_ps(xmm0, [rcx])
endif
    _mm_store_ps(V, xmm6)
    _mm_store_ps(V[16], xmm7)

    inl_XMVectorExp2(xmm0)

    _mm_store_ps(xmm6, V)
    _mm_store_ps(xmm7, V[16])
    ret
XMVectorExp2 endp

    end
