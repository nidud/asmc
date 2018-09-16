
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadFloat3A proc XM_CALLCONV pSource:ptr XMFLOAT3A

    .assert( rcx )
    ;;
    ;; Reads an extra float which is zero'd
    ;;
    _mm_load_ps([rcx])
    _mm_and_ps(xmm0, g_XMMask3)
    ret

XMLoadFloat3A endp

    end
