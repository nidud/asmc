; XMCONVERTFLOATTOHALFSTREAM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXPackedVector.inc

    .code

XMConvertFloatToHalfStream proc XM_CALLCONV uses rsi rdi rbx pOutputStream:ptr HALF, OutputStride:size_t,
        pInputStream:ptr float, InputStride:size_t, FloatCount:size_t

    .assert(pOutputStream)
    .assert(pInputStream)
    .assert(InputStride >= sizeof(float))
    .assert(OutputStride >= sizeof(HALF))

    .for (rsi = r8, rdi = rcx, ebx = 0: rbx < FloatCount: ebx++)

        XMConvertFloatToHalf([rsi])
        mov [rdi],ax
        add rsi,InputStride
        add rdi,OutputStride
    .endf
    mov rax,pOutputStream
    ret

XMConvertFloatToHalfStream endp

    end
