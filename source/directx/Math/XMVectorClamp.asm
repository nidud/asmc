
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorClamp proc XM_CALLCONV V:FXMVECTOR, Min:FXMVECTOR, Max:FXMVECTOR

    inl_XMVectorClamp(xmm0, xmm1, xmm2)
    ret

XMVectorClamp endp

    end
