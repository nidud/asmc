; XMLOADSINT4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadSInt4 proc XM_CALLCONV pSource:ptr XMINT4

    ldr rcx,pSource

    _mm_loadu_si128([rcx])
    ret

XMLoadSInt4 endp

    end
