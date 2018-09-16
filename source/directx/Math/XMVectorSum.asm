
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSum proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSum(xmm0)
    ret

XMVectorSum endp

    end
