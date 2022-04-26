include stdio.inc

    .code

main proc uses rbx r12 argc:int_t, argv:array_t

    .new arg_count:int_t = argc
    .for ( r12 = argv, ebx = 0 : ebx < arg_count : ebx++ )
        printf("[%d]: %s\n", ebx, [r12+rbx*8])
    .endf
    .return( 0 )

main endp

    end
