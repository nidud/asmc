include stdio.inc
include tchar.inc

    .code

main proc argc:int_t, argv:array_t

    printf("dcon_64: Win64 console application\n")
    xor eax,eax
    ret

main endp

    end _tstart

