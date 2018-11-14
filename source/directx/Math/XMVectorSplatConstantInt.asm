; XMVECTORSPLATCONSTANTINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:nosave noauto

XMVectorSplatConstantInt proc XM_CALLCONV IntConstant:int32_t

  local x:XMUINT4

    .assert( IntConstant >= -16 && IntConstant <= 15 )
    ;;
    ;; Splat the int
    ;;
    mov x.x,ecx
    mov x.y,ecx
    mov x.z,ecx
    mov x.w,ecx
    _mm_store_ps(xmm0, x)
    ret

XMVectorSplatConstantInt endp

    end
