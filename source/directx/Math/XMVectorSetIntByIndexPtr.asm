; XMVECTORSETINTBYINDEXPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetIntByIndexPtr proc XM_CALLCONV V:FXMVECTOR, x:ptr uint32_t, i:size_t

    .assert( rdx )
    .assert( r8 < 4 )

    movaps V,xmm0
    mov    eax,[rdx]
    mov    dword ptr V[r8*4],eax
    movaps xmm0,V
    ret

XMVectorSetIntByIndexPtr endp

    end
