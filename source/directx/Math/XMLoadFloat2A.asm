
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat2A proc XM_CALLCONV pSource:ptr XMFLOAT2A

    .assert( rcx )

    _mm_loadl_epi64(rcx)
    ret

XMLoadFloat2A endp

    end
