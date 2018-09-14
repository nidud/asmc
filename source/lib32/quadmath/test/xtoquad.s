include quadmath.inc
include limits.inc

comp64 macro r, i
    local b, q
    .data
    q real16 r
    b real16 0.0
    .code
    i64toquad(addr b, i)
    mov eax,dword ptr b
    mov edx,dword ptr b[4]
    mov ebx,dword ptr q
    mov ecx,dword ptr q[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr b[8]
    mov edx,dword ptr b[12]
    mov ebx,dword ptr q[8]
    mov ecx,dword ptr q[12]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

comp32 macro r, i
    local b, q
    .data
    q real16 r
    b real16 0.0
    .code
    i32toquad(addr b, i)
    mov eax,dword ptr b
    mov edx,dword ptr b[4]
    mov ebx,dword ptr q
    mov ecx,dword ptr q[4]
    .assert( eax == ebx && edx == ecx )
    mov eax,dword ptr b[8]
    mov edx,dword ptr b[12]
    mov ebx,dword ptr q[8]
    mov ecx,dword ptr q[12]
    exitm<.assert( eax == ebx && edx == ecx )>
    endm

comph macro r, h
    local b, q, w
    .data
    q real16 r
    b real16 0.0
    w dw h
    .code
    htoquad(addr b, addr w)
    mov al,byte ptr b[11]
    mov edx,dword ptr b[12]
    mov bl,byte ptr q[11]
    mov ecx,dword ptr q[12]
    exitm<.assert( edx == ecx && al == bl )>
    endm

compqh macro r, h
    local q, w
    .data
    q real16 r
    w dw h
    .code
    quadtoh(addr w, addr q)
    mov ax,w
    mov bx,h
    exitm<.assert( ax == bx )>
    endm

.code

main proc

    comp32(0.0, 0)
    comp32(1.0, 1)
    comp32(2.0, 2)
    comp32(7777777.0, 7777777)
    comp32(2147483647.0, 2147483647)
    comp32(2147483647.0, INT_MAX)
    comp32(-2147483648.0, INT_MIN)
    comp32(-1.0, UINT_MAX)

    comp64(0.0, 0)
    comp64(1.0, 1)
    comp64(2.0, 2)
    comp64(7777777.0, 7777777)
    comp64(9223372036854775807.0, 9223372036854775807)
    comp64(9223372036854775807.0, _I64_MAX)
    comp64(-9223372036854775808.0, _I64_MIN)
    comp64(-1.0, _UI64_MAX)
    .assert( qerrno == 0 )

    comph(0.0, 0)
    comph(1.0, 0x3C00)
    comph(1.000976563, 0x3C01)
    comph(0.0009765625, 0x1400)
    comph(-2.0, 0xC000)
    comph(0.33325196, 0x3555)
    comph(65504.0, 0x7BFF)
    comph(6.103515625e-05, 0x0400)
    comph(6.097555161e-05, 0x03FF)
    comph(5.960464478e-08, 0x0001)
    comph(1.0/0.0, 0x7C00)
    comph(-1.0/0.0, 0xFC00)
    comph(0.0/0.0, 0xFFFF)
    .assert( qerrno == EDOM )

    compqh(0.0, 0)
    compqh(1.0, 0x3C00)
    compqh(1.000976563, 0x3C01)
    compqh(0.0009765625, 0x1400)
    compqh(-2.0, 0xC000)
    compqh(0.33325196, 0x3555)
    compqh(65504.0, 0x7BFF)
    compqh(6.103515625e-05, 0x0400)
    compqh(6.097555161e-05, 0x03FE)
    compqh(5.960464478e-08, 0x0001)
    compqh(1.0/0.0, 0x7C00)
    compqh(-1.0/0.0, 0xFC00)
    compqh(0.0/0.0, 0xFFFF)
    xor eax,eax
    ret

main endp

    end
