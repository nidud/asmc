include stdio.inc

    .code

main proc argc:int_t, argv:array_t

    .new arg_count:int_t = argc
    .new arg_array:ptr_t = argv
    .new i:int_t

    .for ( i = 0 : i < arg_count : i++ )

        mov eax,i
        mov rcx,arg_array

        printf("[%d]: %s\n", i, [rcx+rax*ptr_t])
    .endf
    .return( 0 )

main endp

    end
