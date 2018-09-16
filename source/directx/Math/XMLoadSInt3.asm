
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadSInt3 proc XM_CALLCONV pSource:ptr XMINT3

    .assert( rcx )

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_load_ss(xmm2, [rcx+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    _mm_cvtepi32_ps(_mm_castps_si128(xmm0))
    ret

XMLoadSInt3 endp

    end
