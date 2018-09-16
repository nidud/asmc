
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorSetByIndex proc XM_CALLCONV V:FXMVECTOR, f:float, i:size_t

    movaps V,xmm0
    mov    dword ptr V[r8*4],edx
    movaps xmm0,V
    ret

XMVectorSetByIndex endp

    end
