include intn.inc

.data

_divI label dword
    dq  -1, 1,  -1, 0
    dq  13, 10, 1,  3
    dq  100,    10, 10, 0
    dq  100007, 100000, 1,  7
@divend label byte

.code

udiv128 macro a, b, val, r
    local x, y, z, v
    .data
    x oword a
    y oword b
    z db 16 dup(0)
    v oword val
    .code
    _divnd(addr x, addr y, addr z, 4)
    .assert( z == r )
    mov eax,dword ptr x
    mov edx,dword ptr x[4]
    mov ebx,dword ptr v
    mov ecx,dword ptr v[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr x[8]
    mov edx,dword ptr x[12]
    mov ebx,dword ptr v[8]
    mov ecx,dword ptr v[12]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

main proc
local n[2]

    lea esi,_divI
    .while esi < offset @divend
        _idivn(esi, &[esi+8], &n, 2)
        .assert( !_cmpnd(esi, &[esi+16], 2 ) )
        .assert( !_cmpnd(&n, &[esi+24], 2 ) )
        add esi,4*8
    .endw

    udiv128( 141592653589793238462, 10, 14159265358979323846, 2)
    udiv128( 1415926535897932384626, 10, 141592653589793238462, 6)
    udiv128( 14159265358979323846264, 10, 1415926535897932384626, 4)
    udiv128( 141592653589793238462643, 10, 14159265358979323846264, 3)
    udiv128( 1415926535897932384626433, 10, 141592653589793238462643, 3)
    udiv128( 14159265358979323846264338, 10, 1415926535897932384626433, 8)
    udiv128( 141592653589793238462643383, 10, 14159265358979323846264338, 3)
    udiv128( 1415926535897932384626433832, 10, 141592653589793238462643383, 2)
    udiv128( 14159265358979323846264338327, 10, 1415926535897932384626433832, 7)
    udiv128( 141592653589793238462643383279, 10, 14159265358979323846264338327, 9)
    udiv128( 1415926535897932384626433832795, 10, 141592653589793238462643383279, 5)
    udiv128( 14159265358979323846264338327950, 10, 1415926535897932384626433832795, 0)
    udiv128( 141592653589793238462643383279502, 10, 14159265358979323846264338327950, 2)
    udiv128( 1415926535897932384626433832795028, 10, 141592653589793238462643383279502, 8)

    xor eax,eax
    ret

main endp

    end
