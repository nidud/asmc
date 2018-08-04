
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetByIndexPtr proc XM_CALLCONV V:FXMVECTOR, f:ptr float, i:size_t

    .assert( rdx );
    .assert( r8 < 4 );

    movaps V,xmm0
    mov    eax,[rdx]
    mov    dword ptr V[r8*4],eax
    movaps xmm0,V
    ret

XMVectorSetByIndexPtr endp

    end
