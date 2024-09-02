; XMVECTORSETINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSetInt proc XM_CALLCONV C0:uint32_t, C1:uint32_t, C2:uint32_t, C3:uint32_t

  local x:XMUINT4
    ;;
    ;; Move the parms to a vector
    ;;
    ldr eax,C3
    mov x.w,eax
    ldr eax,C2
    mov x.z,eax
    ldr ecx,C0
    ldr edx,C1
    mov x.x,ecx
    mov x.y,edx
    _mm_store_ps(xmm0, x)
    ret

XMVectorSetInt endp

    end
