
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorCos proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorCos(xmm0)
    ret

XMVectorCos endp

    end
