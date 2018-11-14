; XMVECTORSETINTBYINDEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntByIndex proc XM_CALLCONV V:FXMVECTOR, x:uint32_t, i:size_t

    .assert( r8 < 4 )

    movaps V,xmm0
    mov    dword ptr V[r8*4],edx
    movaps xmm0,V
    ret

XMVectorSetIntByIndex endp

    end
