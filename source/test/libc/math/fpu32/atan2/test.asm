include math.inc
include stdio.inc
include tchar.inc

.code

main proc
local x:real8

    atan2(0.5, 1.5)
    fstp x

    printf("%f\n", x)
    ret

main endp

    end _tstart