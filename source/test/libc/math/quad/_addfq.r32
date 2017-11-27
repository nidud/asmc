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
    _addfq(addr a, addr a, addr b)
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
    compare(1.0, 1.0, 2.0)
    compare(1.1, 1.1, 2.2)
    compare(999999.0001, 1.0001, 1000000.0002)
    compare(0.09, 0.01, 0.1)

    xor eax,eax
    ret

main endp

    end
