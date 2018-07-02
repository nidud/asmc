
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorMod proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorMod(xmm0, xmm1)
    ret

XMVectorMod endp

    end
