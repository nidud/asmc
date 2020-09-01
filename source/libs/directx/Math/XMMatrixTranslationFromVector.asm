; XMMATRIXTRANSLATIONFROMVECTOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixTranslationFromVector proc XM_CALLCONV XMTHISPTR, Offs:FXMVECTOR
if _XM_VECTORCALL_
    _mm_store_ps(xmm1, xmm0)
endif
    _mm_store_ps(xmm0, g_XMIdentityR3.v)
    _mm_store_ps(xmm2, g_XMSelect1110.v)
    _mm_store_ps(xmm3, inl_XMVectorSelect(xmm0, xmm1, xmm2))
    _mm_store_ps(xmm2, g_XMIdentityR2.v)
    _mm_store_ps(xmm1, g_XMIdentityR1.v)
    _mm_store_ps(xmm0, g_XMIdentityR0.v)
if _XM_VECTORCALL_ eq 0
     _mm_store_ps([rcx+0*16], xmm0)
     _mm_store_ps([rcx+1*16], xmm1)
     _mm_store_ps([rcx+2*16], xmm2)
     _mm_store_ps([rcx+3*16], xmm3)
    mov rax,rcx
endif
    ret

XMMatrixTranslationFromVector endp

    end
