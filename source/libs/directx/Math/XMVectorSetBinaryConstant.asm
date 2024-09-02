; XMVECTORSETBINARYCONSTANT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .data
    g_vMask1 XMVECTORU32 { { { 1, 1, 1, 1 } } }

    .code

XMVectorSetBinaryConstant proc XM_CALLCONV uses rbx C0:uint32_t, C1:uint32_t, C2:uint32_t, C3:uint32_t

  local x:XMUINT4

    ;;
    ;; Move the parms to a vector
    ;;
    ldr eax,C3
    ldr ebx,C2
    ldr edx,C1
    ldr ecx,C0

    mov x.x,ecx
    mov x.y,edx
    mov x.z,ebx
    mov x.w,eax

    _mm_store_ps(xmm0, x)
    ;;
    ;; Mask off the low bits
    ;;
    _mm_and_si128(xmm0, g_vMask1)
    ;;
    ;; 0xFFFFFFFF on true bits
    ;;
    _mm_cmpeq_epi32(xmm0, g_vMask1)
    ;;
    ;; 0xFFFFFFFF -> 1.0f, 0x00000000 -> 0.0f
    ;;
    _mm_and_si128(xmm0, g_XMOne)
    ret

XMVectorSetBinaryConstant endp

    end
