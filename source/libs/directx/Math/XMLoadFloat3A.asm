; XMLOADFLOAT3A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadFloat3A proc XM_CALLCONV pSource:ptr XMFLOAT3A

    ldr rcx,pSource
    ;;
    ;; Reads an extra float which is zero'd
    ;;
    _mm_load_ps([rcx])
    _mm_and_ps(xmm0, g_XMMask3)
    ret

XMLoadFloat3A endp

    end
