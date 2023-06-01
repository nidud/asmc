include stdio.inc
include tchar.inc
ifdef _UNICODE
W equ <'W'>
else
W equ <'A'>
endif

pi equ <3.141592653589793238462643383279502884197169399375105820974945>

.data
q REAL16 pi
l REAL10 pi
align 8
d REAL8  pi

.code

_tmain proc

    _tprintf(".lib%d/stdio/quadmath%c:\n"
             "3.141592653589793238462643383279502884197169399375105820974945\n", size_t*8, W)
    _tprintf("%.34llf - %%.34llf\n", q)
    _tprintf("%g - %%g\n", d)
    _tprintf("%Lg - %%Lg\n", l)
    _tprintf("%llg - %%llg\n", q)
    _tprintf("%f - %%f\n", d)
    _tprintf("%Lf - %%Lf\n", l)
    _tprintf("%llf - %%llf\n", q)
    _tprintf("%e - %%e\n", d)
    _tprintf("%Le - %%Le\n", l)
    _tprintf("%lle - %%lle\n", q)
    _tprintf("%.20f - %%.20f\n", d)
    _tprintf("%.24Lf - %%.24Lf\n", l)
    xor eax,eax
    ret

_tmain endp

    end
