include quadmath.inc

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
    _mul256(addr x, addr y, addr z)
    mov eax,dword ptr x[8]
    mov edi,dword ptr x[12]
    mov ebx,dword ptr r[8]
    mov ecx,dword ptr r[12]
    .assert( eax == ebx && edi == ecx )
    mov eax,dword ptr x
    mov edx,dword ptr x[4]
    mov ebx,dword ptr r
    mov ecx,dword ptr r[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr z[8]
    mov edi,dword ptr z[12]
    mov ebx,dword ptr g[8]
    mov ecx,dword ptr g[12]
    .assert( eax == ebx && edi == ecx )
    mov eax,dword ptr z
    mov edx,dword ptr z[4]
    mov ebx,dword ptr g
    mov ecx,dword ptr g[4]
    exitm<.assert( eax == ebx && edx == ecx )>
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
