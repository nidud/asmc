
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadInt4 proc XM_CALLCONV pSource:ptr uint32_t

    .assert( rcx )

    _mm_loadu_si128([rcx])
    ret

XMLoadInt4 endp

    end
