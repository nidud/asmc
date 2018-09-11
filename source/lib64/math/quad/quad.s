include quadmath.inc
include limits.inc

    option epilogue:flags

compare macro op, x, y, z
    local a, b, r
    .data
    a oword x
    b oword y
    r oword z
    .code
    op(addr a, addr b)
    mov rax,qword ptr a
    mov rdx,qword ptr a[8]
    mov rbx,qword ptr r
    mov rcx,qword ptr r[8]
    exitm<.assert( rax == rbx && rdx == rcx )>
    endm

comp64 macro r, i
    local b
    .data
    b real16 r
    .code
    quadtoi64(addr b)
    mov rcx,i
    exitm<.assert(rax == rcx)>
    endm

comp32 macro r, i
    local b
    .data
    b real16 r
    .code
    quadtoi32(addr b)
    mov edx,i
    exitm<.assert(eax == edx)>
    endm

comprr macro a, b
    mov rax,qword ptr a
    mov rdx,qword ptr a+8
    mov rbx,qword ptr b
    mov rcx,qword ptr b+8
    exitm<.assert(rax == rbx && rdx == rcx)>
    endm

compval macro a, val
    local b
    .data
    b real16 val
    .code
    exitm<comprr(a, b)>
    endm

comparea macro a, val, p, e
    compval(a, val)
    mov rdx,p
    mov al,[rdx]
    exitm<.assert(al == e)>
    endm

.code

main proc

  local x:REAL16
  local y:REAL16
  local exponent:dword
  local eptr:LPSTR

    comp32(0.0, 0)
    comp32(0.10, 0)
    comp32(1.0, 1)
    comp32(2.0, 2)
    comp32(0.99999999, 0)
    comp32(7777777.0, 7777777)
    comp32(2147483647.0, 2147483647)
    .assert( qerrno == 0 )
    comp32(100000000000000000000.0, INT_MAX)
    .assert( qerrno == ERANGE )
    comp32(-100000000000000000000.0, INT_MIN)

    mov qerrno,0
    comp64(0.0, 0)
    comp64(0.10, 0)
    comp64(1.0, 1)
    comp64(2.0, 2)
    comp64(0.99999999, 0)
    comp64(7777777.0, 7777777)
    comp64(9223372036854775807.0, 9223372036854775807)
    .assert( qerrno == 0 )
    comp64(9223372036854775808.0, _I64_MAX)
    .assert( qerrno == ERANGE )
    comp64(-9223372036854775808.0, _I64_MIN)

    compare(quadadd, 0.0, 0.0, 0.0)
    compare(quadadd, 1.0, 0.0, 1.0)
    compare(quadadd, -1.0, 0.0, -1.0)
    compare(quadadd, 1.0, 1.0, 2.0)
    compare(quadadd, 1.1, 1.1, 2.2)
    compare(quadadd, 999999.0001, 1.0001, 1000000.0002)
    compare(quadadd, 0.09, 0.01, 0.1)

    compare(quadsub, 0.0, 0.0, 0.0)
    compare(quadsub, 1.0, 0.0, 1.0)
    compare(quadsub, -1.0, 0.0, -1.0)
    compare(quadsub, 1.0, 1.0, 0.0)
    compare(quadsub, 1.1, 1.1, 0.0)
    compare(quadsub, 10000000.0002, 999999.0001, 9000001.0001 )

    compare(quaddiv, 0.0, 0.0, 0x7FFF8000000000000000000000000000)
    compare(quaddiv, 0.0, 1.0, 0.0)
    compare(quaddiv, 0.0, -1.0, 0.0)
    compare(quaddiv, 2.0, 1.0, 2.0)
    compare(quaddiv, 1.1, 2.2, 0.5)
    compare(quaddiv, 0.01, 0.1, 0.1)
    compare(quaddiv, 66666.6, 2.0, 33333.3)
    ; 0x3FEB0C7659426EB346F3B91986814E5F
    compare(quaddiv, 1.0001, 1000000.0002, 0x3FEB0C7659426EB346F3B91986814E5E)

    compare(quadmul, 0.0, 0.0, 0.0)
    compare(quadmul, 0.0, 1.0, 0.0)
    compare(quadmul, 0.0, -1.0, 0.0)
    compare(quadmul, 2.0, 1.0, 2.0)
    ; 0x400035C28F5C28F5C28F5C28F5C28F5C - 2.42
    compare(quadmul, 1.1, 2.2, 0x400035C28F5C28F5C28F5C28F5C28F5A)
    ; 0x3FF50624DD2F1A9FBE76C8B439581062 - 1.e-03
    compare(quadmul, 0.01, 0.1, 0x3FF50624DD2F1A9FBE76C8B439581061)
    ; 0x4012E8548001A378EB79354B10749756 - 1000100.0002
    compare(quadmul, 1.0001, 1000000.0002, 0x4012E8548001A378EB79354B10749755)

    atoquad(&x, ".", &eptr )
    comparea(x, 0.0, eptr, '.')
    atoquad(&x, "-1.0e-0a", &eptr )
    comparea(x, -1.0, eptr, 'a')
    atoquad(&x, "-1e-0a", &eptr )
    comparea(x, -1.0, eptr, 'a')
    atoquad(&x, "123456789.0", &eptr )
    comparea(x, 123456789.0, eptr, 0)

    xor eax,eax
    ret

main endp

    end
