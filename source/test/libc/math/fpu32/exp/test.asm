include math.inc
include stdio.inc
include tchar.inc

.code

main proc
local x:real8

    exp(3.54)
    fstp x

    printf("%f\n", x)
    ret

main endp

    end _tstart