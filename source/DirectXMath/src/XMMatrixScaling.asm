
include DirectXMath.inc

    .data

    x XMFLOAT4 { 0.0, 0.0, 0.0, 1.0 }
    y XMFLOAT4 { 0.0, 0.0, 1.0, 0.0 }
    z XMFLOAT4 { 0.0, 1.0, 0.0, 0.0 }

    .code

    option win64:rsp nosave noauto

XMMatrixScaling proc XM_CALLCONV XMTHISPTR, ScaleX:float, ScaleY:float, ScaleZ:float
if _XM_VECTORCALL_
    movss x.w,xmm0
    movss y.z,xmm1
    movss z.y,xmm2
else
    movss x.w,xmm1
    movss y.z,xmm2
    movss z.y,xmm3
endif
    _mm_store_ps(xmm0, x)
    _mm_store_ps(xmm1, y)
    _mm_store_ps(xmm2, z)
    _mm_store_ps(xmm3, g_XMIdentityR3.v)
if _XM_VECTORCALL_ eq 0
     _mm_store_ps([rcx+0*16], xmm0)
     _mm_store_ps([rcx+1*16], xmm1)
     _mm_store_ps([rcx+2*16], xmm2)
     _mm_store_ps([rcx+3*16], xmm3)
    mov rax,rcx
endif
    ret

XMMatrixScaling endp

    end
