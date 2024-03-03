include math.inc
include stdio.inc
include tchar.inc

.code

main proc

  local x:real8

    atan2(1.0, 2.0)
ifdef __SSE__
    movsd x,xmm0
else
    fstp x
endif
    printf("%f\n", x)
    xor eax,eax
    ret

main endp

    end _tstart