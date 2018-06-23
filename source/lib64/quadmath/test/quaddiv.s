include quadmath.inc
include limits.inc
include errno.inc

compare macro x, y, z
    local a, b, r
    .data
    a real16 x
    b real16 y
    r oword z
    .code
    quaddiv(addr a, addr b)
    mov rax,qword ptr a
    mov rdx,qword ptr a[8]
    mov rbx,qword ptr r
    mov rcx,qword ptr r[8]
    exitm<.assert(rax == rbx && rdx == rcx)>
    endm

.code

main proc

    compare(0.0, 0.0, 0x7FFF0000000000000000000000000000)
    compare(0.0, 1.0, 0.0)
    compare(0.0, -1.0, 0.0)
    compare(2.0, 1.0, 2.0)
    compare(1.1, 2.2, 0.5)
    compare(0.01, 0.1, 0.1)
    compare(66666.6, 2.0, 33333.3)
    ; 0x3FEB0C7659426EB346F3B91986814E5F
    compare(1.0001, 1000000.0002, 0x3FEB0C7659426EB346F3B91986814E5E)
    xor eax,eax
    ret

main endp

    end
