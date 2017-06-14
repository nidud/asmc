include conio.inc
include ctype.inc
include tchar.inc

.code

main proc

    _cputs("Type 'Y' when finished typing keys: ")
    .repeat
        _getch()
        toupper(eax)
    .until al == 'Y'

    _putch(eax)   ;
    _putch(13)    ; Carriage return
    _putch(10)    ; Line feed
    xor eax,eax
    ret

main endp

    end _tstart
