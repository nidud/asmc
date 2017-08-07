include intn.inc

.code

mul2 macro val, m, res
    local x, y, z, r
    .data
    x dq val
    y dq m
    r dq res
    z dq 0
    .code
    _mulnd(addr x, addr y, addr z, 2)
    mov eax,dword ptr x
    mov edx,dword ptr x[4]
    mov ebx,dword ptr r
    mov ecx,dword ptr r[4]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

mul4 macro val, m, res, h
    local x, y, z, r, g
    .data
    x oword val
    y oword m
    r oword res
    z oword 0
    g oword h
    .code
    _mulnd(addr x, addr y, addr z, 4)
    mov eax,dword ptr x
    mov edx,dword ptr x[4]
    mov ebx,dword ptr r
    mov ecx,dword ptr r[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr x[8]
    mov edx,dword ptr x[12]
    mov ebx,dword ptr r[8]
    mov ecx,dword ptr r[12]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr z
    mov edx,dword ptr z[4]
    mov ebx,dword ptr g
    mov ecx,dword ptr g[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr z[8]
    mov edx,dword ptr z[12]
    mov ebx,dword ptr g[8]
    mov ecx,dword ptr g[12]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

main proc

    mul2( 0, 0, 0 )
    mul2( 1, 1, 1 )
    mul2( 2, 1, 2 )
    mul2( 20, 10, 200 )
    mul2( 33, 10, 330 )
    mul2( 100000, 100000, 10000000000 )
    mul2( 100000, 1000000, 100000000000 )
    mul2( 100000, 10000000, 1000000000000 )
    mul2( 1000000, 10000000, 10000000000000 )
    mul2( 20000000, 10000000, 200000000000000 )
    mul2( 0x1000000000000000, 3, 0x3000000000000000 )
    mul2( 0x7FFFFFFFFFFFFFFF, 2, 0xFFFFFFFFFFFFFFFE )
    mul2( 0x7FFFFFFFFFFFFFFF, 3, 0x7FFFFFFFFFFFFFFD )

    mul4( 0, 0, 0, 0 )
    mul4( 1, 1, 1, 0 )
    mul4( 2, 1, 2, 0 )
    mul4( 20, 10, 200, 0 )
    mul4( 33, 10, 330, 0 )
    mul4( 100000, 100000, 10000000000, 0 )
    mul4( 100000, 1000000, 100000000000, 0 )
    mul4( 100000, 10000000, 1000000000000, 0 )
    mul4( 1000000, 10000000, 10000000000000, 0 )
    mul4( 20000000, 10000000, 200000000000000, 0 )
    mul4( 0x100000000000000000000000, 3, 0x300000000000000000000000, 0 )
    mul4( 0x7FFFFFFFFFFFFFFF, 2, 0xFFFFFFFFFFFFFFFE, 0 )
    mul4( 0x7FFFFFFFFFFFFFFF, 3, 0x17FFFFFFFFFFFFFFD, 0 )

    mul4( 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF, 2, 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE, 0 )
    mul4( 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF, 3, 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFD, 1 )

    xor eax,eax
    ret

main endp

    end
