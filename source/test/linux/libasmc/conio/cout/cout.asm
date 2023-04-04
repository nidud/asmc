; _COUT.ASM--
;
; https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
;

include conio.inc

.code

main proc

   .new w:int_t = 0
   .new h:int_t = 0

    _cout(ESC "7" )         ; push cursor
    _cout(CSI "500;500H" )  ; goto x;y (to big)
    _cout(CSI "6n" )        ; read position

    .repeat

        .break .if ( _getch() != 27 )
        .break .if ( _getch() != '[' )

        _getch()
        .while ( eax >= '0' && eax <= '9' )

            imul ecx,h,10
            sub  eax,'0'
            add  eax,ecx
            mov  h,eax
            _getch()
        .endw
        .break .if ( eax != ';' )

        _getch()
        .while ( eax >= '0' && eax <= '9' )

            imul ecx,w,10
            sub  eax,'0'
            add  eax,ecx
            mov  w,eax
            _getch()
        .endw
    .until 1
    _cout(ESC "8" ) ; pop cursor
    _cout("The size of the console is \e[7m %d:%d \e[0m\n\n", w, h)
    _getch()
   .return(0)

main endp

    end
