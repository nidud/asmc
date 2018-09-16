
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorLess proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorLess(xmm0, xmm1)
    ret

XMVectorLess endp

    end
