; XMCONVERTVECTORUINTTOFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMConvertVectorUIntToFloat proc XM_CALLCONV VInt:FXMVECTOR, DivExponent:uint32_t

    ldr xmm0,VInt
    ldr edx,DivExponent

    _mm_store_ps(xmm1, xmm0)
    ;;
    ;; For the values that are higher than 0x7FFFFFFF, a fixup is needed
    ;; Determine which ones need the fix.
    ;;
    _mm_and_ps(xmm1, g_XMNegativeZero)
    ;;
    ;; Force all values positive
    ;;
    _mm_xor_ps(xmm0, xmm1)
    ;;
    ;; Convert to floats
    ;;
    _mm_cvtepi32_ps(xmm0)
    ;;
    ;; Convert 0x80000000 -> 0xFFFFFFFF
    ;;
    _mm_srai_epi32(xmm1, 31)
    ;;
    ;; For only the ones that are too big, add the fixup
    ;;
    _mm_and_ps(xmm1, g_XMFixUnsigned)
    _mm_add_ps(xmm1, xmm0)
    ;;
    ;; Convert DivExponent into 1.0f/(1<<DivExponent)
    ;;
    ;; uint32_t uScale = 0x3F800000U - (DivExponent << 23);
    ;;
    ;; Splat
    ;;
    shl edx,23
    mov eax,0x3F800000
    sub eax,edx
    movd xmm0,eax
    _mm_mul_ps(XM_PERMUTE_PS(), xmm1)
    ret

XMConvertVectorUIntToFloat endp

    end
