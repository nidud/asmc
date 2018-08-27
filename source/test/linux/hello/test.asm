; build:
; asmc -elf64 test.asm
; gcc -o test test.o

include stdio.inc

.code

main proc

    printf( "Hello Linux!\n" )
    ret

main endp

    end