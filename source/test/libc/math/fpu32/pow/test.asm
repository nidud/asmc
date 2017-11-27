include math.inc
include stdio.inc
include tchar.inc

.code

main proc
local x:real8

    pow(0.5, 2.0)
    fstp x

    printf("%f\n", x)
    ret

main endp

    end _tstart