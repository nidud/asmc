
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorInBoundsR proc XM_CALLCONV pCR:ptr uint32_t, V:FXMVECTOR, Bounds:FXMVECTOR

    _mm_store_ps(xmm0, xmm1)
    ;; Test if less than or equal
    _mm_cmple_ps(xmm0, xmm2)
    ;; Negate the bounds
    _mm_mul_ps(xmm2, g_XMNegativeOne)
    ;; Test if greater or equal (Reversed)
    _mm_cmple_ps(xmm2, xmm1)
    ;; Blend answers
    _mm_and_ps(xmm0, xmm2)
    xor edx,edx
    .if _mm_movemask_ps() == 0x0F
        ;;
        ;; All elements are in bounds
        ;;
        mov edx,XM_CRMASK_CR6BOUNDS
    .endif
    mov [rcx],edx
    ret

XMVectorInBoundsR endp

    end
