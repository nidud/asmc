include intn.inc
include limits.inc
include errno.inc

comp64 macro r, i
    local b
    .data
    b real16 r
    .code
    _qftoll(addr b)
    mov rcx,i
    exitm<.assert(rax == rcx)>
    endm

comp32 macro r, i
    local b
    .data
    b real16 r
    .code
    _qftol(addr b)
    mov edx,i
    exitm<.assert(eax == edx)>
    endm

.code

main proc

    comp32(0.0, 0)
    comp32(0.10, 0)
    comp32(1.0, 1)
    comp32(2.0, 2)
    comp32(0.99999999, 0)
    comp32(7777777.0, 7777777)
    comp32(2147483647.0, 2147483647)
    .assert( errno == 0 )
    comp32(100000000000000000000.0, INT_MAX)
    .assert( errno == ERANGE )
    comp32(-100000000000000000000.0, INT_MIN)

    mov errno,0
    comp64(0.0, 0)
    comp64(0.10, 0)
    comp64(1.0, 1)
    comp64(2.0, 2)
    comp64(0.99999999, 0)
    comp64(7777777.0, 7777777)
    comp64(9223372036854775807.0, 9223372036854775807)
    .assert( errno == 0 )
    comp64(9223372036854775808.0, _I64_MAX)
    .assert( errno == ERANGE )
    comp64(-9223372036854775808.0, _I64_MIN)

    xor eax,eax
    ret

main endp

    end
