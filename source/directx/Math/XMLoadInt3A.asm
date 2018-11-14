; XMLOADINT3A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadInt3A proc XM_CALLCONV pSource:ptr uint32_t

    .assert( rcx )
    ;;
    ;; Reads an extra integer which is zero'd
    ;;
    _mm_load_si128([rcx])
    _mm_and_si128(xmm0, g_XMMask3)
    ret

XMLoadInt3A endp

    end
