
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorNotEqual proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorNotEqual(xmm0, xmm1)
    ret

XMVectorNotEqual endp

    end
