
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMVectorReplicate proc XM_CALLCONV Value:float

    XM_PERMUTE_PS()
    ret

XMVectorReplicate endp

    end
