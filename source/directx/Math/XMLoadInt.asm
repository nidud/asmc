
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadInt proc XM_CALLCONV pSource:ptr uint32_t

    .assert( rcx )

    _mm_load_ss(xmm0, [rcx])
    _mm_load_ss(xmm1, [rcx+4])
    _mm_unpacklo_ps(xmm0, xmm1)
    ret

XMLoadInt endp

    end
