
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixLookToLH proc XM_CALLCONV XMTHISPTR, EyePosition:FXMVECTOR, EyeDirection:FXMVECTOR, UpDirection:FXMVECTOR

    _mm_store_ps(EyePosition, xmm6)
    _mm_store_ps(EyeDirection, xmm7)
if _XM_VECTORCALL_
    inl_XMMatrixLookToLH(xmm0, xmm1, xmm2)
else
    inl_XMMatrixLookToLH(xmm1, xmm2, xmm3)
    _mm_store_ps([rcx+0*16], xmm0)
    _mm_store_ps([rcx+1*16], xmm1)
    _mm_store_ps([rcx+2*16], xmm2)
    _mm_store_ps([rcx+3*16], xmm3)
    mov rax,rcx
endif
    _mm_store_ps(xmm6, EyePosition)
    _mm_store_ps(xmm7, EyeDirection)
    ret

XMMatrixLookToLH endp

    end
