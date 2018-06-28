
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMConvertVectorIntToFloat proc XM_CALLCONV VInt:FXMVECTOR, DivExponent:uint32_t
    ;;
    ;; Convert DivExponent into 1.0f/(1<<DivExponent)
    ;;
    ;; uScale = 0x3F800000 - (DivExponent << 23)
    ;;
    ;; Splat the scalar value
    ;;
    shl edx,23
    mov eax,0x3F800000
    sub eax,edx
    movd xmm1,eax
    _mm_mul_ps(_mm_cvtepi32_ps(), XM_PERMUTE_PS(xmm1))
    ret

XMConvertVectorIntToFloat endp

    end
