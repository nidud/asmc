
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMConvertVectorFloatToInt proc XM_CALLCONV VFloat:FXMVECTOR, MulExponent:uint32_t

    mov ecx,edx
    mov eax,1
    sal eax,cl

    _mm_cvt_si2ss(xmm1, eax)
    _mm_mul_ps(xmm0, XM_PERMUTE_PS(xmm1, _MM_SHUFFLE(0,0,0,0)))
    ;;
    ;; In case of positive overflow, detect it
    ;;
    ;; Note: cmpltps xmm2,xmm0
    ;;
    _mm_cmpgt_ps(xmm0, _mm_store_ps(xmm2, g_XMMaxInt))
    ;;
    ;; Float to int conversion
    ;;
    _mm_cvttps_epi32(xmm1, xmm0)
    ;;
    ;; If there was positive overflow, set to 0x7FFFFFFF
    ;;
    _mm_and_ps(_mm_store_ps(xmm0, g_XMAbsMask), xmm2)
    _mm_andnot_ps(xmm2, _mm_castsi128_ps(xmm1))
    _mm_or_ps(xmm0, xmm2)
    ret

XMConvertVectorFloatToInt endp

    end
