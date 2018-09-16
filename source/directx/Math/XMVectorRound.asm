
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorRound proc XM_CALLCONV V:FXMVECTOR

    inl_XMVectorRound(xmm0)
    ret

XMVectorRound endp

    end
