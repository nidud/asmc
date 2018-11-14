; XMVECTORINSERT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

XMVectorInsert proc XM_CALLCONV VD:FXMVECTOR, VS:FXMVECTOR, VSLeftRotateElements:uint32_t,
        Select0:uint32_t, Select1:uint32_t, Select2:uint32_t, Select3:uint32_t

  local Control:XMVECTOR, V1:XMVECTOR, V2:XMVECTOR, VSLeft:uint32_t

    movaps V1,xmm0
    movaps V2,xmm1
    mov VSLeft,r8d

    and r9d,1
    mov ecx,r9d
    mov edx,Select1
    mov r8d,Select2
    mov r9d,Select3
    and r8d,1
    and edx,1
    and ecx,1

    XMVectorSelectControl(ecx, edx, r8d, r9d)
    movaps Control,xmm0
    XMVectorRotateLeft(V2, VSLeft)
    movaps xmm1,xmm0
    XMVectorSelect(V1, xmm1, Control)
    ret

XMVectorInsert endp

    end
