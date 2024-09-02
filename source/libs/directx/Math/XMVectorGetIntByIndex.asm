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

XMVectorGetIntByIndex proc XM_CALLCONV V:FXMVECTOR, i:size_t

    mov eax,dword ptr V[rdx*4]
    ret

XMVectorGetIntByIndex endp

    end
