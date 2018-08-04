
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorTrueInt proc XM_CALLCONV

    mov eax,-1
    movd xmm0,eax
    XM_PERMUTE_PS()
    ret

XMVectorTrueInt endp

    end
