
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSplatZ proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSplatZ()
    ret

XMVectorSplatZ endp

    end
