
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorNorInt proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorNorInt(xmm0, xmm1)
    ret

XMVectorNorInt endp

    end
