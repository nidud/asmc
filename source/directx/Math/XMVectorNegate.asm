
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorNegate proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorNegate(xmm0)
    ret

XMVectorNegate endp

    end
