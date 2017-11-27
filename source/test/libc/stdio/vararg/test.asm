include stdio.inc
include stdlib.inc
include tchar.inc

    .code

_tmain proc

    printf("%lli\n", 0xFFFFFFFFFFFFFFFF)
    printf("%lli\n", 0x7FFFFFFFFFFFFFFF)
    ret

_tmain endp

    end _tstart
