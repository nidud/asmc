
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat3 proc XM_CALLCONV pSource:ptr XMFLOAT3

    .assert( rcx )

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_load_ss(xmm2, [rcx+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    ret

XMLoadFloat3 endp

    end
