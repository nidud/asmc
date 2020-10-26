include math.inc
include stdio.inc
include tchar.inc

    .code

main proc

    cosh(1.0)
    printf("%f\n", xmm0)
    ret

main endp

    end _tstart