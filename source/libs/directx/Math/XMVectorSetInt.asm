; XMVECTORSETINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:nosave noauto

XMVectorSetInt proc XM_CALLCONV C0:uint32_t, C1:uint32_t, C2:uint32_t, C3:uint32_t

  local x:XMUINT4
    ;;
    ;; Move the parms to a vector
    ;;
    mov x.x,ecx
    mov x.y,edx
    mov x.z,r8d
    mov x.w,r9d

    _mm_store_ps(xmm0, x)
    ret

XMVectorSetInt endp

    end
