include conio.inc
include ctype.inc
include stdlib.inc

.code

main proc

    _cputs( "Type 'Y' when finished typing keys: " )

    .repeat

        toupper( _getch()  )

    .until  al == 'Y'

    _putch( eax )   ;
    _putch( 13 )    ; Carriage return
    _putch( 10 )    ; Line feed

    exit(0)

main endp

    end main
