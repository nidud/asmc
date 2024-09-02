; XMVECTORSPLATCONSTANT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatConstant proc XM_CALLCONV IntConstant:int32_t, DivExponent:uint32_t

  local x:XMUINT4

    ldr ecx,IntConstant
    ldr edx,DivExponent
    ;;
    ;; Splat the int
    ;;
    mov x.x,ecx
    mov x.y,ecx
    mov x.z,ecx
    mov x.w,ecx
    _mm_store_ps(xmm1, x)
    ;;
    ;; Convert to a float
    ;;
    _mm_cvtepi32_ps(xmm1)
    ;;
    ;; Convert DivExponent into 1.0f/(1<<DivExponent)
    ;;
    ;; uint32_t uScale = 0x3F800000U - (DivExponent << 23);
    ;; Splat the scalar value (It's really a float)
    ;;
    shl edx,23
    mov eax,0x3F800000
    sub eax,edx
    movd xmm0,eax
    ;;
    ;; Multiply by the reciprocal (Perform a right shift by DivExponent)
    ;;
    _mm_mul_ps(xmm0, xmm1)
    ret

XMVectorSplatConstant endp

    end
