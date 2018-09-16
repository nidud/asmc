
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorMergeZW proc XM_CALLCONV V1:FXMVECTOR, V2:FXMVECTOR

    inl_XMVectorMergeZW(xmm0, xmm1)
    ret

XMVectorMergeZW endp

    end
