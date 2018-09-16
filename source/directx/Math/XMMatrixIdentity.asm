
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixIdentity proc XM_CALLCONV XMTHISPTR

    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
if _XM_VECTORCALL_ eq 0
     _mm_store_ps([rcx+0*16], xmm0)
     _mm_store_ps([rcx+1*16], xmm1)
     _mm_store_ps([rcx+2*16], xmm2)
     _mm_store_ps([rcx+3*16], xmm3)
    mov rax,rcx
endif
    ret

XMMatrixIdentity endp

    end
