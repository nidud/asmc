
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorCeiling proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorCeiling(xmm0)
    ret

XMVectorCeiling endp

    end
