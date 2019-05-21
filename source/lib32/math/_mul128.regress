include winnt.inc

_mul128 proto Multiplier: DWORD64, Multiplicand: DWORD64, HighProduct: ptr DWORD64

.code

mul2 macro val, m, res
    local r
    .data
    r dq res
    .code
    _mul128(val, m, 0)
    mov ebx,dword ptr r
    mov ecx,dword ptr r[4]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

mul4 macro val, m, l, h
    local r, x, y
    .data
    r dq 0
    x dq l
    y dq h
    .code
    _mul128(val, m, addr r)
    mov ebx,dword ptr x
    mov ecx,dword ptr x[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr y
    mov edx,dword ptr y[4]
    mov ebx,dword ptr r
    mov ecx,dword ptr r[4]
    exitm<.assert( ebx == eax && edx == ecx )>
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
    mul4( 0x1000000000000000, 3, 0x3000000000000000, 0 )
    mul4( 0x7FFFFFFFFFFFFFFF, 2, 0xFFFFFFFFFFFFFFFE, 0 )
    mul4( 0x7FFFFFFFFFFFFFFF, 3, 0x7FFFFFFFFFFFFFFD, 0x1 )
    mul4( 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0x00000000000000001, 0xFFFFFFFFFFFFFFFE )

    xor eax,eax
    ret

main endp

    end
