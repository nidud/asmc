; XMSTOREHALF2.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include DirectXPackedVector.inc

    .code

XMStoreHalf2 proc XM_CALLCONV uses rbx pDestination:ptr XMHALF2, V:FXMVECTOR

    ldr rbx,pDestination
    ldr xmm0,V

    XMConvertFloatToHalf(xmm0)
    mov [rbx].XMHALF2.x,ax
    XM_PERMUTE_PS(xmm0, _MM_SHUFFLE(0, 3, 2, 1))
    XMConvertFloatToHalf(xmm0)
    mov [rbx].XMHALF2.y,ax
    ret

XMStoreHalf2 endp

    end
