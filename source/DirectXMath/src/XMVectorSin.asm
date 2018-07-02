
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSin proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSin(xmm0)
    ret

XMVectorSin endp

    end
