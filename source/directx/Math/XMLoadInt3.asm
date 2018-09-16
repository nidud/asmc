
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadInt3 proc XM_CALLCONV pSource:ptr uint32_t

    .assert( rcx )

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_load_ss(xmm3, [rcx+8])
    _mm_unpacklo_ps(xmm0, xmm1)
    _mm_movelh_ps(xmm0, xmm2)
    ret

XMLoadInt3 endp

    end
