include quadmath.inc
include limits.inc

compare macro op, x, y, z
    local r
    .data
ifnb <z>
    r oword z
    .code
    op(x, y)
else
    r oword y
    .code
    op(x)
endif
    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rcx,xmm0
    mov     rbx,qword ptr r
    mov     rdx,qword ptr r[8]
    .assert( rax == rbx && rcx == rdx )
    exitm<>
    endm

.code

main proc

    compare(atanq, 0.0, 0.0)
    compare(atanq, 1.5, 0.9827937232473290679857106110146660710)
    compare(atan2q, 0.0, 0.0, 0.0)
    compare(atan2q, 0.5, 1.5, 0.3217505543966421934014046143586613)
    compare(sqrtq, 0.0, 0.0)
    compare(sqrtq, 1.0, 1.0)
    compare(sqrtq, 2.0, 1.4142135623730950488016887242097016)

    compare(addq, 0.0, 0.0, 0.0)
    compare(addq, 1.0, 0.0, 1.0)
    compare(addq, -1.0, 0.0, -1.0)
    compare(addq, 1.0, 1.0, 2.0)
    compare(addq, 1.1, 1.1, 2.2)
    compare(addq, 999999.0001, 1.0001, 1000000.0002)
    compare(addq, 0.09, 0.01, 0.1)

    compare(subq, 0.0, 0.0, 0.0)
    compare(subq, 1.0, 0.0, 1.0)
    compare(subq, -1.0, 0.0, -1.0)
    compare(subq, 1.0, 1.0, 0.0)
    compare(subq, 1.1, 1.1, 0.0)
    compare(subq, 10000000.0002, 999999.0001, 9000001.0001 )

    compare(mulq, 0.0, 0.0, 0.0)
    compare(mulq, 0.0, 1.0, 0.0)
    compare(mulq, 0.0, -1.0, 0.0)
    compare(mulq, 2.0, 1.0, 2.0)

    ; TODO:
    ; 0x400035C28F5C28F5C28F5C28F5C28F5C - 2.42
    compare(mulq, 1.1, 2.2, 0x400035C28F5C28F5C28F5C28F5C28F5A)
    ; 0x3FF50624DD2F1A9FBE76C8B439581062 - 1.e-03
    compare(mulq, 0.01, 0.1, 0x3FF50624DD2F1A9FBE76C8B439581061)
    ; 0x4012E8548001A378EB79354B10749756 - 1000100.0002
    compare(mulq, 1.0001, 1000000.0002, 0x4012E8548001A378EB79354B10749755)

    compare(divq, 0.0, 0.0, 0x7FFF8000000000000000000000000000)
    compare(divq, 0.0, 1.0, 0.0)
    compare(divq, 0.0, -1.0, 0.0)
    compare(divq, 2.0, 1.0, 2.0)
    compare(divq, 1.1, 2.2, 0.5)
    compare(divq, 0.01, 0.1, 0.1)
    compare(divq, 66666.6, 2.0, 33333.3)
    ; 0x3FEB0C7659426EB346F3B91986814E5F
    compare(divq, 1.0001, 1000000.0002, 0x3FEB0C7659426EB346F3B91986814E5E)

    .assertd( qtoi32(0.0) == 0 )
    .assertd( qtoi32(1.0) == 1 )
    .assertd( qtoi32(1.9) == 1 )
    .assertd( qtoi32(-2.0) == -2 )
    .assertd( qtoi32(333332.0) == 333332 )

    compare(i32toq, 100, 100.0)
    compare(i32toq, -100, -100.0)
    compare(i32toq, 33333, 33333.0)
    compare(i32toq, 666, 666.0)

    xor eax,eax
    ret

main endp

    end
