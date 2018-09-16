
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSinCosEst proc XM_CALLCONV pSin:ptr XMVECTOR, pCos:ptr XMVECTOR, Value:FXMVECTOR

    inl_XMVectorSinCosEst(xmm2)
    movaps [rcx],xmm0
    movaps [rdx],xmm1
    ret

XMVectorSinCosEst endp

    end
