; XMMATRIXPERSPECTIVEFOVLH.ASM--
; Copyright (C) 2018 Asmc Developers

include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixPerspectiveFovLH proc XM_CALLCONV XMTHISPTR, FovAngleY:float, AspectRatio:float, NearZ:float, FarZ:float
if _XM_VECTORCALL_
    inl_XMMatrixPerspectiveFovLH(xmm0,xmm1,xmm2,xmm3)
else
    assume rcx:ptr XMMATRIX
    inl_XMMatrixPerspectiveFovLH(xmm1,xmm2,xmm3,xmm4,[rcx])
    mov rax,rcx
endif
    ret

XMMatrixPerspectiveFovLH endp

    end
