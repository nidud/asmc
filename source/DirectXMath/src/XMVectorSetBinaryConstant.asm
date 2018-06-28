
include DirectXMath.inc

    .data
    g_vMask1 XMVECTORU32 { { { 1, 1, 1, 1 } } }

    .code

    option win64:nosave noauto

XMVectorSetBinaryConstant proc XM_CALLCONV C0:uint32_t, C1:uint32_t, C2:uint32_t, C3:uint32_t

  local x:XMUINT4
    ;;
    ;; Move the parms to a vector
    ;;
    mov x.x,ecx
    mov x.y,edx
    mov x.z,r8d
    mov x.w,r9d
    ;_mm_set_epi32(C3, C2, C1, C0)
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
