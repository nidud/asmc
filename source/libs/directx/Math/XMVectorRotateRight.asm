; XMVECTORROTATERIGHT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:nosave

XMVectorRotateRight proc XM_CALLCONV V:FXMVECTOR, Elements:uint32_t

    .assert( edx < 4 )

    mov eax,edx

    mov edx,4
    mov r8d,5
    mov r9d,6
    mov r10d,7

    sub edx,eax
    sub r8d,eax
    sub r9d,eax
    sub r10d,eax

    and edx,3
    and r8d,3
    and r9d,3
    and r10d,3

    XMVectorSwizzle(xmm0, edx, r8d, r9d, r10d)
    ret

XMVectorRotateRight endp

    end
