; XMLOADINT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadInt4 proc XM_CALLCONV pSource:ptr uint32_t

    ldr rcx,pSource

    _mm_loadu_si128([rcx])
    ret

XMLoadInt4 endp

    end
