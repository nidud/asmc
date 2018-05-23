include quadmath.inc

    option epilogue:flags

compare macro x, y, z
    local a, b, r
    .data
    a real16 x
    b real16 y
    r oword z
    .code
    quadmul(addr a, addr b)
    mov rax,qword ptr a
    mov rdx,qword ptr a[8]
    mov rbx,qword ptr r
    mov rcx,qword ptr r[8]
    exitm<.assert( rax == rbx && rdx == rcx )>
    endm

.code

main proc

    compare(0.0, 0.0, 0.0)
    compare(0.0, 1.0, 0.0)
    compare(0.0, -1.0, 0.0)
    compare(2.0, 1.0, 2.0)

    ; TODO:
    ; 0x400035C28F5C28F5C28F5C28F5C28F5C - 2.42
    compare(1.1, 2.2, 0x400035C28F5C28F5C28F5C28F5C28F5A)
    ; 0x3FF50624DD2F1A9FBE76C8B439581062 - 1.e-03
    compare(0.01, 0.1, 0x3FF50624DD2F1A9FBE76C8B439581061)
    ; 0x4012E8548001A378EB79354B10749756 - 1000100.0002
    compare(1.0001, 1000000.0002, 0x4012E8548001A378EB79354B10749755)

    xor eax,eax
    ret

main endp

    end
