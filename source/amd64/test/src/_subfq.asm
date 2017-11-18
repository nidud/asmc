include intn.inc
include limits.inc
include errno.inc

    option epilogue:flags

compare macro x, y, z
    local a, b, r
    .data
    a real16 x
    b real16 y
    r real16 z
    .code
    _subfq(addr a, addr a, addr b)
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
    compare(1.0, 1.0, 0.0)
    compare(1.1, 1.1, 0.0)
;    compare(0.10, 0.09, 0.01)
;    compare(10000000.0002, 999999.0001, 9000001.0001 )

    xor eax,eax
    ret

main endp

    end
