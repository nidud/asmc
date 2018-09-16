
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixTranslation proc XM_CALLCONV XMTHISPTR, OffsetX:float, OffsetY:float, OffsetZ:float

if _XM_VECTORCALL_
    movss [rsp+8],xmm0
    movss [rsp+8][4],xmm1
    movss [rsp+8][8],xmm2
else
    movss [rsp+8],xmm1
    movss [rsp+8][4],xmm2
    movss [rsp+8][8],xmm3
endif
    mov real4 ptr [rsp+8][12],1.0
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_store_ps(xmm3, [rsp+8] )
if _XM_VECTORCALL_ eq 0
     _mm_store_ps([rcx+0*16], xmm0)
     _mm_store_ps([rcx+1*16], xmm1)
     _mm_store_ps([rcx+2*16], xmm2)
     _mm_store_ps([rcx+3*16], xmm3)
    mov rax,rcx
endif
    ret

XMMatrixTranslation endp

    end
