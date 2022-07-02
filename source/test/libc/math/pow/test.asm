include math.inc
include stdio.inc
include tchar.inc

.code

main proc

  local x:real8

    pow(2.5, 3.4)
ifdef _WIN64
    movsd x,xmm0
else
    fstp x
endif
    printf("%f\n", x)
    ret

main endp

    end _tstart