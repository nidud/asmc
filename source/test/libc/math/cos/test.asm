include math.inc
include stdio.inc
include tchar.inc

    .code

_tmain proc

  local x:real8

    movsd x,cos(10.0)
    printf("%.14f\n", x)
    ret

_tmain endp

    end _tstart