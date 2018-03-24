include intn.inc

compare macro x, y, z
    local a, b, r
    .data
    a real16 x
    b real16 y
    r oword z
    .code
    _mulfq(addr a, addr a, addr b)
    mov eax,dword ptr a[8]
    mov edi,dword ptr a[12]
    mov ebx,dword ptr r[8]
    mov ecx,dword ptr r[12]
    .assert( eax == ebx && edi == ecx )
    mov eax,dword ptr a
    mov edx,dword ptr a[4]
    mov ebx,dword ptr r
    mov ecx,dword ptr r[4]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

.code

main proc

    compare(0.0, 0.0, 0.0)
    compare(0.0, 1.0, 0.0)
    compare(0.0, -1.0, 0.0)
    compare(2.0, 1.0, 2.0)
    ; 0x400035C28F5C28F5C28F5C28F5C28F5C - 2.42
    compare(1.1, 2.2, 0x400035C28F5C28F5C28F5C28F5C28F5A)
    ;0x3FF50624DD2F1A9FBE76C8B439581062 - 1.e-03
    compare(0.01, 0.1, 0x3FF50624DD2F1A9FBE76C8B439581061)
    ;0x4012E8548001A36E2EB1C432CA57A786 - 1000100.0002
    compare(1.0001, 1000000.0002, 0x4012E8548001A378EB79354B10749755)

    xor eax,eax
    ret

main endp

    end
