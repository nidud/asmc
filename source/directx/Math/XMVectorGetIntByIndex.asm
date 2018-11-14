; XMVECTORGETINTBYINDEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Return an integer value via an index. This is not a recommended
; function to use due to performance loss.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntByIndex proc XM_CALLCONV V:FXMVECTOR, i:size_t

    movaps V,xmm0
    mov    eax,dword ptr V[r8*4]
    ret

XMVectorGetIntByIndex endp

    end
