
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSplatX proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSplatX()
    ret

XMVectorSplatX endp

    end
