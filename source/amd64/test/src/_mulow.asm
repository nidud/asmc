include intn.inc

.code

mulo macro val, m, res, h
    local x, y, z, r, g
    .data
    x oword val
    y oword m
    r oword res
    z oword 0
    g oword h
    .code
    _mulow(addr x, addr y, addr z)
    mov rax,qword ptr x
    mov rcx,qword ptr r
    .assert( rax == rcx )
    mov rdx,qword ptr x[8]
    mov rbx,qword ptr r[8]
    .assert( rdx == rbx )
    mov rax,qword ptr z
    mov rcx,qword ptr g
    .assert( rax == rcx )
    mov rdx,qword ptr z[8]
    mov rbx,qword ptr g[8]
    exitm<.assert( rdx == rbx )>
    endm

main proc

    mulo( 0, 0, 0, 0 )
    mulo( 1, 1, 1, 0 )
    mulo( 2, 1, 2, 0 )
    mulo( 20, 10, 200, 0 )
    mulo( 33, 10, 330, 0 )
    mulo( 100000, 100000, 10000000000, 0 )
    mulo( 100000, 1000000, 100000000000, 0 )
    mulo( 100000, 10000000, 1000000000000, 0 )
    mulo( 1000000, 10000000, 10000000000000, 0 )
    mulo( 20000000, 10000000, 200000000000000, 0 )
    mulo( 0x100000000000000000000000, 3, 0x300000000000000000000000, 0 )
    mulo( 0x7FFFFFFFFFFFFFFF, 2, 0xFFFFFFFFFFFFFFFE, 0 )
    mulo( 0x7FFFFFFFFFFFFFFF, 3, 0x17FFFFFFFFFFFFFFD, 0 )
    mulo( 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF, 2, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE, 0 )
    mulo( 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF, 3, 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD, 1 )

    xor eax,eax
    ret

main endp

    end
