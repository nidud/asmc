include string.inc
include stdio.inc

.code

main proc argc:int_t, argv:array_t

    printf(".lib%d/stdlib/argv:\n", size_t*8)

    .for ( bx = 0 : bx < argc : bx++ )

        lesl di,argv
        imul ax,bx,string_t
        add di,ax
        mov ax,esl[di]
        movl dx,es:[di+2]
        printf( " [%d] %s\n", bx, rax )
    .endf
    xor ax,ax
    ret

main endp

    end
