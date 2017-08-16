include intn.inc
include limits.inc
include errno.inc

    option epilogue:flags

compare macro r, e
    local a, b
    .data
    a real16 r
    b real16 ?
    .code
    _qpow10(addr b, e)
    mov eax,dword ptr a
    mov edx,dword ptr a[4]
    mov ebx,dword ptr b
    mov ecx,dword ptr b[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr a[8]
    mov edx,dword ptr a[12]
    mov ebx,dword ptr b[8]
    mov ecx,dword ptr b[12]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

.code

main proc

    compare(0.0, 0)
    compare(10.0, 1)
    compare(100.0, 2)
    compare(1000.0, 3)
    compare(1.e4, 4)
    compare(1.e8, 8)
    compare(0.1, -1)
    compare(0.01, -2)

    xor eax,eax
    ret

main endp

    end
