include stdio.inc
include tchar.inc

    .code

main proc argc:int_t, argv:array_t

    printf("con_32: Win32 console application\n")
    xor eax,eax
    ret

main endp

    end _tstart

