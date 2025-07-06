include stdio.inc

.code

main proc argc:int_t, argv:array_t

    mov  di,word ptr argv
    movl si,word ptr argv[2]

    .for ( bx = 0 : bx < argc : bx++, di+=string_t )

        movl es,si
        mov  ax,esl[di]
        movl dx,es:[di+2]

        printf( " [%d] %s\n", bx, ldr(ax) )
    .endf
    .return( 0 )

main endp

    end
