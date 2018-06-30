
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSplatW proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorSplatW()
    ret

XMVectorSplatW endp

    end
