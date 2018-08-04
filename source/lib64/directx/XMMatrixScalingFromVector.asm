
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixScalingFromVector proc XM_CALLCONV XMTHISPTR, Scale:FXMVECTOR
if _XM_VECTORCALL_
    _mm_store_ps(xmm1, xmm0)
    _mm_store_ps(xmm2, xmm0)
else
    _mm_store_ps(xmm0, xmm1)
    _mm_store_ps(xmm2, xmm1)
endif
    _mm_and_ps(xmm0, g_XMMaskX)
    _mm_and_ps(xmm1, g_XMMaskY)
    _mm_and_ps(xmm2, g_XMMaskZ)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
if _XM_VECTORCALL_ eq 0
     _mm_store_ps([rcx+0*16], xmm0)
     _mm_store_ps([rcx+1*16], xmm1)
     _mm_store_ps([rcx+2*16], xmm2)
     _mm_store_ps([rcx+3*16], xmm3)
    mov rax,rcx
endif
    ret

XMMatrixScalingFromVector endp

    end
