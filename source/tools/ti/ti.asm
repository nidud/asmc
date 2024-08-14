
; Simple benchmark for assembly time

include time.inc
include stdio.inc
include stdlib.inc
include string.inc

    .code

main proc argc:int_t, argv:array_t

    .new cmd[1024]:sbyte

    .if ( argc > 1 )

        mov rbx,argv
        add rbx,string_t*2
        strcpy(&cmd, [rbx-string_t])

        .for ( : argc > 2 : argc--, rbx+=string_t )

            strcat(&cmd, " ")
            strcat(&cmd, [rbx])
        .endf

        mov ebx,clock()
        system(&cmd)
        clock()
        sub eax,ebx
        mov ebx,eax
        printf("%5d ClockTicks: %s\n", ebx, &cmd)
    .else
        printf("TimeIt Version 1.02 Public Domain\n"
               "Usage: ti <command> <args>\n\n")
    .endif
    xor eax,eax
    ret

main endp

    end
