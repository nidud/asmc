
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat4A proc XM_CALLCONV pSource:ptr XMFLOAT4A

    .assert( rcx )

    _mm_load_ps([rcx])
    ret

XMLoadFloat4A endp

    end
