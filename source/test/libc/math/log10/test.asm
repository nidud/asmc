include math.inc
include stdio.inc
include tchar.inc

    .code

_tmain proc

  local x:real8

    log10(10.0)
ifdef __SSE__
    movsd x,xmm0
else
    fstp x
endif
    printf("%f\n", x)
    xor eax,eax
    ret

_tmain endp

    end _tstart