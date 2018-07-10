
include DirectXMath.inc

    .code

    option win64:rsp nosave noauto

XMMatrixMultiply proc XM_CALLCONV XMTHISPTR, M1:CXMMATRIX, M2:CXMMATRIX

    _mm_store_ps([rsp+8], xmm6)
if _XM_VECTORCALL_
    inl_XMMatrixMultiply( [rcx], [rdx] )
else
    inl_XMMatrixMultiply( [rdx], [r8], [rcx] )
    mov rax,rcx
endif
    _mm_store_ps(xmm6, [rsp+8])
    ret

XMMatrixMultiply endp

    end
