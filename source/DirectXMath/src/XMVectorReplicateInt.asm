
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReplicateInt proc XM_CALLCONV Value:uint32_t

    movd xmm0,ecx
    XM_PERMUTE_PS()
    ret

XMVectorReplicateInt endp

    end
