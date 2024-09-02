; XMLOADFLOAT3X3.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMLoadFloat3x3 proc XM_CALLCONV pSource:ptr XMFLOAT3X3

    ldr rcx,pSource

    _mm_loadu_ps(xmm2, [rcx][12][4])
    _mm_load_ss(xmm4, [rcx][24][8])
    _mm_setzero_ps(xmm5)
    _mm_loadu_ps(xmm0, [rcx])
    _mm_store_ps(xmm1, xmm2)
    _mm_shuffle_ps(xmm2, xmm4, _MM_SHUFFLE(1, 0, 3, 2))
    _mm_unpacklo_ps(xmm1, xmm5)
    _mm_store_ps(xmm3, xmm0)
    _mm_unpackhi_ps(xmm3, xmm5)
    _mm_shuffle_ps(xmm4, xmm1, _MM_SHUFFLE(0, 1, 0, 0))
    _mm_movelh_ps(xmm0, xmm3)
    _mm_movehl_ps(xmm1, xmm4)
    _mm_movehl_ps(xmm5, xmm3)
    _mm_add_ps(xmm1, xmm5)
    _mm_store_ps(xmm3, g_XMIdentityR3)
    ret

XMLoadFloat3x3 endp

    end
