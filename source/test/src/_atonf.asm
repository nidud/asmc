include intn.inc

_MAX equ 8

.code

main proc
local n[_MAX]
local eptr:LPSTR
local exponent:dword
local x:REAL10
local y:REAL10

comprr macro a, b
    mov eax,dword ptr a
    mov edx,dword ptr a+4
    mov si,word ptr a+8
    mov ebx,dword ptr b
    mov ecx,dword ptr b+4
    mov di,word ptr b+8
    exitm<.assert(eax == ebx && ecx == edx && si == di)>
    endm

compval macro a, val
    local b
    .data
    b dt val
    .code
    exitm<comprr(a, b)>
    endm

compare macro a, val, p, e
    compval(a, val)
    mov edx,p
    mov al,[edx]
    exitm<.assert(al == e)>
    endm

    _atonf(&x, "-1.0e-0a", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compare(x, -1.0, eptr, 'a')
    _atonf(&x, "-1e-0a", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compare(x, -1.0, eptr, 'a')

    _atonf(&x, ".", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compare(x, 0.0, eptr, '.')

    _atonf(&n, "1.12", 0, &exponent, Q_SIGBITS, Q_EXPBITS, 4 )
    .assert( exponent == -2 )
    _atonf(&n, "0.123456789", 0, &exponent, Q_SIGBITS, Q_EXPBITS, 4 )
    .assert( exponent == -9 )
    _atonf(&n, "0.123456789", 0, &exponent, O_SIGBITS, O_EXPBITS, 8 )
    .assert( exponent == -9 )

    _atonf(&x, "123456789.0", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compare(x, 123456789.0, eptr, 0)

    _atonf(&x, "0x1g", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compare(x, 1.0, eptr, 'g')

    _atonf(&x, "0x2", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compval(x, 2.0)

    _atonf(&x, "0x4", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compval(x, 4.0)

    _atonf(&x, "0x8", &eptr, &exponent, LD_SIGBITS, LD_EXPBITS, 3 )
    compval(x, 8.0)

    xor eax,eax
    ret

main endp

    end
