include stdio.inc
include limits.inc

.code

main proc

  local i:int_t

    printf(".lib%d/stdio/format_%c(%%b):\n", size_t*8, 'b')

    .for ( i = 10 : i < 16 : i++ )

        printf("%9X  %04b  %d\n", i, i, i)
    .endf
    printf(" %lX  %032lb  %ld\n", INT_MAX, INT_MAX, INT_MAX)
    printf(" %lX  %032lb  %ld\n", INT_MIN, INT_MIN, INT_MIN)
    xor ax,ax
    ret

main endp

    end
