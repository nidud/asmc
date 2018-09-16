
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSplatY proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSplatY()
    ret

XMVectorSplatY endp

    end
