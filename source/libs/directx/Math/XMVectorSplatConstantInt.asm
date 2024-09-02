; XMVECTORSPLATCONSTANTINT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorSplatConstantInt proc XM_CALLCONV IntConstant:int32_t

    ldr     ecx,IntConstant
    ;;
    ;; Splat the int
    ;;
    movd     xmm0,ecx
    shufps   xmm0,xmm0,0
    ret

XMVectorSplatConstantInt endp

    end
