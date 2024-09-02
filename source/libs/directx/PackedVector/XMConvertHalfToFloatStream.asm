; XMCONVERTHALFTOFLOATSTREAM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include DirectXPackedVector.inc

    .code

XMConvertHalfToFloatStream proc XM_CALLCONV uses rsi rdi rbx pOutputStream:ptr float, OutputStride:size_t,
        pInputStream:ptr HALF, InputStride:size_t, HalfCount:size_t

    .assert(pOutputStream)
    .assert(pInputStream)
    .assert(InputStride >= sizeof(HALF))
    .assert(OutputStride >= sizeof(float))

    .for (rsi = r8, rdi = rcx, ebx = 0: rbx < HalfCount: ebx++)

        XMConvertHalfToFloat([rsi])
        mov [rdi],eax
        add rsi,InputStride
        add rdi,OutputStride
    .endf

    mov rax,pOutputStream
    ret

XMConvertHalfToFloatStream endp

    end
