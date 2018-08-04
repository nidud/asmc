
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadInt4A proc XM_CALLCONV pSource:ptr uint32_t

    .assert( rcx )

    _mm_load_si128([rcx])
    ret

XMLoadInt4A endp

    end
