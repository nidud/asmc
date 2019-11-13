include math.inc
include stdio.inc
include tchar.inc

.code

main proc

  local x:real8

    movsd x,sin(1.0)
    printf("%f\n", x)
    ret

main endp

    end _tstart