include math.inc
include stdio.inc
include tchar.inc

    .code

_tmain proc

  local x:real8

    sqrt(3.14159265358979323846264338327950288419716939937511)
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