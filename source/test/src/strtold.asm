include io.inc
include stdio.inc
include stdlib.inc
include string.inc

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
    fstp a
    exitm<comprr(a, b)>
    endm

compare macro a, val, p, e
    compval(a, val)
    mov edx,p
    mov al,[edx]
    exitm<.assert(al == e)>
    endm

.data

.code

main proc
local eptr:LPSTR
local x:REAL10
local y:REAL10

    _strtold("3.14159265358979323846264338327", NULL)
    compval(x, 3.14159265358979323846264338327)

    _strtold("1.1920928955078125E-007", NULL)
    fstp x
    _strtold("0x1P-23", NULL)
    fstp y
    comprr(x, y)

    _strtold("-1.0e-0a", &eptr)
    compare(x, -1.0, eptr, 'a')

    _strtold(".", &eptr)
    compare(x, 0.0, eptr, '.')

    _strtold("+3.14159265", &eptr)
    ;compare(x, 3.14159265, eptr, 0)

    _strtold("-0", NULL)
    compval(x, 0)

    _strtold("0x1g", &eptr)
    compare(x, 1.0, eptr, 'g')

    _strtold("0x2", &eptr)
    compval(x, 2.0)

    _strtold("0x4", &eptr)
    compval(x, 4.0)

    _strtold("0x8", NULL)
    compval(x, 8.0)

    _strtold("0x10", &eptr)
    compval(x, 16.0)

    _strtold("-0x10.0p-0z", &eptr)
    compare(x, -16.0, eptr, 'z')

    _strtold("-0x100.0P-8P", &eptr)
    compare(x, -1.0, eptr, 'P')

    _strtold("0x.cq", &eptr)
    compare(x, 0.75, eptr, 'q')

    _strtold("0x.0000Ap20", &eptr)
    compval(x, 10.0)

    _strtold("0xF.a", &eptr)
    compval(x, 15.625)

    _strtold("0xfAp-04", &eptr)
    compval(x, 15.625)

    _strtold("0x1..0p3", &eptr)
    compval(x, 1.0)
    .assert( !strcmp(eptr, ".0p3") )

    _strtold("0x0000000000000000000000000000000000000000000000001234567890123j", &eptr)
;    compare(x, 0x1234567890123, eptr, 'j')
;    compare(x, 1.582274e0305, eptr, 'j')
    mov edx,eptr
    mov al,[edx]
    .assert(al == 'j')

    _strtold("-0x1p-1a", &eptr)
    compare(x, -0.5, eptr, 'a')

    _strtold("NaNumber", &eptr)
    ;.assert(isnan(x) && !signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 'u')

    _strtold("NAN()", &eptr)
    ;.assert(isnan(x) && !signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 0)

    _strtold("-nan(non_sense_354)", &eptr)
    ;.assert(isnan(x) && signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 0)

    _strtold("Infiniti", &eptr)
    ;.assert(isinf(x) && !signbit(x))
    .assert(!strcmp(eptr, "initi"))

    _strtold("InFiNiTy01", &eptr )
    ;.assert(isinf(x) && !signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 'i')

    _strtold("-INF", NULL)
    ;.assert(isinf(x) && signbit(x))

    _strtold("1.0e99999", NULL)
    ;.assert(isinf(x) && !signbit(x))

    _strtold("-1.0e99999", NULL)
    ;.assert(isinf(x) && signbit(x))
    ret

main endp

    end
