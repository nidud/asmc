; XMVECTORSETINTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntW proc XM_CALLCONV V:FXMVECTOR, x:uint32_t

    inl_XMVectorSetIntW(xmm0, edx)
    ret

XMVectorSetIntW endp

    end
