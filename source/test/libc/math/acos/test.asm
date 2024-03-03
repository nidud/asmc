include math.inc
include stdio.inc
include tchar.inc

    .code

_tmain proc

  .new x:real8

    acos(0.5)
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