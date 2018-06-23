include quadmath.inc

    option epilogue:flags

compare macro x, y, z
    local a, b, r
    .data
    a real16 x
    b real16 y
    r real16 z
    .code
    quadadd(addr a, addr b)
    mov rax,qword ptr a
    mov rdx,qword ptr a[8]
    mov rbx,qword ptr r
    mov rcx,qword ptr r[8]
    exitm<.assert( rax == rbx && rdx == rcx )>
    endm

.code

main proc

    compare(0.0, 0.0, 0.0)
    compare(1.0, 0.0, 1.0)
    compare(-1.0, 0.0, -1.0)
    compare(1.0, 1.0, 2.0)
    compare(1.1, 1.1, 2.2)
    compare(999999.0001, 1.0001, 1000000.0002)
    compare(0.09, 0.01, 0.1)
    xor eax,eax
    ret

main endp

    end
