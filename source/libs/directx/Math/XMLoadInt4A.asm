; XMLOADINT4A.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMLoadInt4A proc XM_CALLCONV pSource:ptr uint32_t

    .assert( rcx )

    _mm_load_si128([rcx])
    ret

XMLoadInt4A endp

    end
