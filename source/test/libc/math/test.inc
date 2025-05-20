include math.inc
include stdio.inc
include tchar.inc

ifdef _WIN64
define BITS 64
else
define BITS 32
endif
ifdef __PE__
define INFO <"msvcrt">
else
define INFO <"libc">
endif

    .code

_tmain proc

  local x:real8

    FUNC(VALUE)
ifdef _WIN64
ifdef ISFLOAT
    cvtss2sd xmm0,xmm0
endif
    movsd x,xmm0
else
    fstp x
endif
    _tprintf("%.14f " INFO "(%d)\n", x, BITS)
    xor eax,eax
    ret

_tmain endp

    end _tstart
