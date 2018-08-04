
include DirectXMath.inc

    .code

    option win64:nosave noauto

XMVectorGetByIndex proc XM_CALLCONV V:FXMVECTOR, i:size_t

  local U:XMVECTORF32

    _mm_store_ps(U.v, xmm0)
    _mm_store_ss(xmm0, U.f[rdx*4])
    ret

XMVectorGetByIndex endp

    end
