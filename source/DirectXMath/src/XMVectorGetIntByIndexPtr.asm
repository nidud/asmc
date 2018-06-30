
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorGetIntByIndexPtr proc XM_CALLCONV f:ptr uint32_t, V:FXMVECTOR, i:size_t

    movaps xmmword ptr f,xmm0
    mov    eax,dword ptr f[r8*4]
    mov    [rcx],eax
    ret

XMVectorGetIntByIndexPtr endp

    end
