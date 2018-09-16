
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

.data
    r2 real2 1.0,2.0,3.0,4.0
    r4 real4 1.0,2.0,3.0,4.0
    b2 real2 4 dup(?)
    b4 real4 4 dup(?)
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

    XMConvertHalfToFloatStream(&b4, 4, &r2, 2, 4)
    lea rsi,b4
    .assert( rsi == rax )
    .for( ecx = 0, rdx = &r4: ecx < 4: ecx++, rdx += 4 )
        lodsd
        .assert( eax == [rdx] )
    .endf

    XMConvertFloatToHalfStream(&b2, 2, &r4, 4, 4)
    lea rsi,b2
    .assert( rsi == rax )
    .for( ecx = 0, rdx = &r2: ecx < 4: ecx++, rdx += 2 )
        lodsw
        .assert( ax == [rdx] )
    .endf

    xor eax,eax
    ret

main endp

    end
