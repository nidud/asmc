include quadmath.inc
include limits.inc

    option epilogue:flags

compare macro x, y, z
    local a, b, r
    .data
    a real16 x
    b real16 y
    r real16 z
    .code
    quadsub(addr a, addr b)
    mov eax,dword ptr a
    mov edx,dword ptr a[4]
    mov ebx,dword ptr r
    mov ecx,dword ptr r[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr a[8]
    mov edx,dword ptr a[12]
    mov ebx,dword ptr r[8]
    mov ecx,dword ptr r[12]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

.code

main proc

    compare(0.0, 0.0, 0.0)
    compare(1.0, 0.0, 1.0)
    compare(-1.0, 0.0, -1.0)
    compare(1.0, 1.0, 0.0)
    compare(1.1, 1.1, 0.0)
    ;compare(10000000.0002, 999999.0001, 9000001.0001 )
    xor eax,eax
    ret

main endp

    end
