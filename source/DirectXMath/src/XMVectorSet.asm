
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSet proc XM_CALLCONV C0:float, C1:float, C2:float, C3:float

    inl_XMVectorSet(xmm0,xmm1,xmm2,xmm3)
    ret

XMVectorSet endp

    end
