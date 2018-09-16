
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReciprocal proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorReciprocal(xmm0)
    ret

XMVectorReciprocal endp

    end
