
include DirectXPackedVector.inc


comph macro i
    local r
    .data
    r real2 i
    .code
    XMConvertFloatToHalf(i)
    ;movd eax,xmm0
    mov bx,r
    exitm<.assert( ax == bx )>
    endm

compf macro i
    local r
    .data
    r real4 i
    .code
    XMConvertHalfToFloat(i)
    ;movd eax,xmm0
    mov ebx,r
    exitm<.assert( eax == ebx )>
    endm

.code

main proc

    comph(0.0)
    comph(1.0)
    comph(2.0)
    comph(-2.0)
    comph(65504.0)
    comph(1.000976563)
    comph(0.0009765625)
    comph(0.33325196)
    comph(6.103515625e-05)

    compf(0.0)
    compf(1.0)
    compf(2.0)
    compf(-2.0)
    compf(65504.0)
    compf(1.000976563)
    compf(0.0009765625)
    compf(0.33325196)
    compf(6.103515625e-05)

    xor eax,eax
    ret

main endp

    end
