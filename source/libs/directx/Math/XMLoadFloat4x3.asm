; XMLOADFLOAT4X3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadFloat4x3 proc XM_CALLCONV pSource:ptr XMFLOAT4X3

    ldr rcx,pSource

    _mm_loadu_ps(xmm1, [rcx][12][4])
    _mm_loadu_ps(xmm3, [rcx][24][8])
    _mm_store_ps(xmm4, g_XMMask3)
    _mm_loadu_ps(xmm0, [rcx][0][0])
    _mm_store_ps(xmm2, xmm1)
    _mm_shuffle_ps(xmm2, xmm3, _MM_SHUFFLE(0,0,3,2))
    _mm_srli_si128(xmm3, 32/8)
    _mm_shuffle_ps(xmm1, xmm0, _MM_SHUFFLE(3,3,1,0))
    _mm_and_ps(xmm2, xmm4)
    _mm_or_ps(xmm3, g_XMIdentityR3)
    _mm_and_ps(xmm0, xmm4)
    _mm_shuffle_ps(xmm1, xmm1, _MM_SHUFFLE(1,1,0,2))
    _mm_and_ps(xmm1, xmm4)
    ret

XMLoadFloat4x3 endp

    end
