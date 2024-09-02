; XMSTOREU565.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreU565 proc XM_CALLCONV pDestination:ptr XMU565, V:FXMVECTOR

    ldr rcx,pDestination
    ldr xmm0,V

    ;; Bounds check

    _mm_max_ps(xmm0, g_XMZero)
    _mm_min_ps(xmm0, _mm_get_epi32(31.0, 63.0, 31.0, 0.0))

    ;; Convert to int with rounding

    _mm_cvtps_epi32(xmm0)

    ;; No SSE operations will write to 16-bit values, so we have to extract them manually

    movd    eax,xmm0
    and     eax,0x1F
    shufps  xmm0,xmm0,01001110B
    movd    edx,xmm0
    and     edx,0x3F
    shl     edx,5
    or      eax,edx
    movq    rdx,xmm0
    shr     rdx,32
    and     edx,0x1F
    shl     edx,11
    or      eax,edx
    mov     [rcx].XMU565.v,ax
    ret

XMStoreU565 endp

    end
