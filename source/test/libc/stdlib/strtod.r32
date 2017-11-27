include io.inc
include stdio.inc
include stdlib.inc
include string.inc

comprr macro a, b
    mov eax,dword ptr a
    mov edx,dword ptr a+4
    mov ebx,dword ptr b
    mov ecx,dword ptr b+4
    exitm<.assert (eax == ebx && ecx == edx)>
    endm

compval macro a, val
    local b
    .data
    b dq val
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
local x:REAL8
local y:REAL8

    strtod("3.14159265358979323846264338327", NULL)
    compval(x, 3.14159265358979323846264338327)

    strtod("1.1920928955078125E-007", NULL)
    fstp x
    strtod("0x1P-23", NULL)
    fstp y
    comprr(x, y)

    strtod("-1.0e-0a", &eptr)
    compare(x, -1.0, eptr, 'a')

    strtod(".", &eptr)
    compare(x, 0.0, eptr, '.')

    strtod("+3.14159265", &eptr)
    compare(x, 3.14159265, eptr, 0)

    strtod("-0", NULL)
    compval(x, 0)

    strtod("0x1g", &eptr)
    compare(x, 1.0, eptr, 'g')

    strtod("0x2", &eptr)
    compval(x, 2.0)

    strtod("0x4", &eptr)
    compval(x, 4.0)

    strtod("0x8", NULL)
    compval(x, 8.0)

    strtod("0x10", &eptr)
    compval(x, 16.0)

    strtod("-0x10.0p-0z", &eptr)
    compare(x, -16.0, eptr, 'z')

    strtod("-0x100.0P-8P", &eptr)
    compare(x, -1.0, eptr, 'P')

    strtod("0x.cq", &eptr)
    compare(x, 0.75, eptr, 'q')

    strtod("0x.0000Ap20", &eptr)
    compval(x, 10.0)

    strtod("0xF.a", &eptr)
    compval(x, 15.625)

    strtod("0xfAp-04", &eptr)
    compval(x, 15.625)

    strtod("0x1..0p3", &eptr)
    compval(x, 1.0)
    .assert( !strcmp(eptr, ".0p3") )

    ;strtod("0x0000000000000000000000000000000000000000000000001234567890123j", &eptr)
    ;compare(x, 0x1234567890123, eptr, 'j')

    strtod("-0x1p-1a", &eptr)
    compare(x, -0.5, eptr, 'a')

    strtod("NaNumber", &eptr)
    ;.assert(isnan(x) && !signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 'u')

    strtod("NAN()", &eptr)
    ;.assert(isnan(x) && !signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 0)

    strtod("-nan(non_sense_354)", &eptr)
    ;.assert(isnan(x) && signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 0)

    strtod("Infiniti", &eptr)
    ;.assert(isinf(x) && !signbit(x))
    .assert(!strcmp(eptr, "initi"))

    strtod("InFiNiTy01", &eptr )
    ;.assert(isinf(x) && !signbit(x))
    mov edx,eptr
    mov al,[edx]
    .assert(al == 'i')

    strtod("-INF", NULL)
    ;.assert(isinf(x) && signbit(x))

    strtod("1.0e99999", NULL)
    ;.assert(isinf(x) && !signbit(x))

    strtod("-1.0e99999", NULL)
    ;.assert(isinf(x) && signbit(x))
    ret

main endp

    end
