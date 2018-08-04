
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorAbs proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorAbs(xmm0)
    ret

XMVectorAbs endp

    end
