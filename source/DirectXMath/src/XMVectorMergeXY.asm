
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorMergeXY proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorMergeXY(xmm0, xmm1)
    ret

XMVectorMergeXY endp

    end
