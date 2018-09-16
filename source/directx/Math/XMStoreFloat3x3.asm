
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMStoreFloat3x3 proc XM_CALLCONV pDestination:ptr XMFLOAT3X3, AXMMATRIX3
if _XM_VECTORCALL_
    inl_XMStoreFloat3x3([rcx])
else
    assume rdx:ptr XMMATRIX
    inl_XMStoreFloat3x3([rcx],[rdx])
endif
    ret

XMStoreFloat3x3 endp

    end
