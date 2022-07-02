include math.inc
include stdio.inc
include tchar.inc

    .code

_tmain proc

  local x:real8

    exp(3.54)
ifdef __SSE__
    movsd x,xmm0
else
    fstp x
endif
    printf("%.18f\n", x)
    ret

_tmain endp

    end _tstart