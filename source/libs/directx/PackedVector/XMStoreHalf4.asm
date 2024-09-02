; XMSTOREHALF4.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreHalf4 proc XM_CALLCONV uses rbx pDestination:ptr XMHALF4, V:FXMVECTOR

    ldr rbx,pDestination
    ldr xmm0,V

    XMConvertFloatToHalf(xmm0)
    mov [rbx],ax
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm0)
    mov [rbx+2],ax
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm0)
    mov [rbx+4],ax
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm0)
    mov [rbx+6],ax
    mov rax,rbx
    ret

XMStoreHalf4 endp

    end
