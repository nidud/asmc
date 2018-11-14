; XMCONVERTVECTORFLOATTOUINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMConvertVectorFloatToUInt proc XM_CALLCONV VFloat:FXMVECTOR, MulExponent:uint32_t

    mov ecx,edx
    mov eax,1
    sal eax,cl
    _mm_xor_ps(xmm1, xmm1)
    _mm_cvt_si2ss(xmm1, eax)
    XM_PERMUTE_PS(xmm1)

    _mm_mul_ps(xmm1, xmm0)
    ;;
    ;; Clamp to >=0
    ;;
    _mm_max_ps(xmm1, g_XMZero)
    ;;
    ;; Any numbers that are too big, set to 0xFFFFFFFFU
    ;;
    _mm_store_ps(xmm3, g_XMUnsignedFix)
    _mm_store_ps(xmm4, g_XMMaxUInt)
    _mm_store_ps(xmm2, xmm3)
    _mm_cmpgt_ps(xmm4, xmm1, xmm4)
    ;;
    ;; Too large for a signed integer?
    ;;
    _mm_cmpge_ps(xmm2, xmm1, xmm2)
    ;;
    ;; Zero for number's lower than 0x80000000, 32768.0f*65536.0f otherwise
    ;;
    _mm_and_ps(xmm3, xmm2)
    ;;
    ;; Perform fixup only on numbers too large (Keeps low bit precision)
    ;;
    _mm_sub_ps(xmm1, xmm3)
    _mm_cvttps_epi32(xmm0, xmm1)
    ;;
    ;; Convert from signed to unsigned pnly if greater than 0x80000000
    ;;
    _mm_and_ps(xmm2, g_XMNegativeZero)
    _mm_xor_ps(xmm0, xmm2)
    ;;
    ;; On those that are too large, set to 0xFFFFFFFF
    ;;
    _mm_or_ps(xmm0, xmm4)
    ret

XMConvertVectorFloatToUInt endp

    end
