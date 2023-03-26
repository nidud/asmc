; _COUT.ASM--
;
; https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
;

include conio.inc
include ctype.inc
include tchar.inc

define ESC <"\e">
define CSI <"\e[">

.code

_tmain proc argc:int_t, argv:array_t

   .new w:int_t = 0
   .new h:int_t = 0

    _cout(ESC "7" )         ; push cursor
    _cout(CSI "500;500H" )  ; goto x;y (to big)
    _cout(CSI "6n" )        ; read position

    .repeat

        .break .if ( _getch() != 27 )
        .break .if ( _getch() != '[' )

        mov edi,_getch()
        .while isdigit(edi)

            imul eax,h,10
            sub  edi,'0'
            add  eax,edi
            mov  h,eax
            mov  edi,_getch()
        .endw
        .break .if ( edi != ';' )

        mov edi,_getch()
        .while isdigit(edi)

            imul eax,w,10
            sub  edi,'0'
            add  eax,edi
            mov  w,eax
            mov  edi,_getch()
        .endw
    .until 1
    _cout(ESC "8" ) ; pop cursor
    _cout("The size of the console is \e[7m%d:%d\e[0m\n\n", w, h)
   .return(0)

_tmain endp

    end _tstart
