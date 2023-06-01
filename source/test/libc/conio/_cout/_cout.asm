; _COUT.ASM--
;
; https://learn.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
;

include conio.inc
include ctype.inc
include tchar.inc

.code

_tmain proc argc:int_t, argv:array_t

   .new w:int_t
   .new h:int_t
ifndef __TTY__
    SetConsoleMode(_confh, ENABLE_PROCESSED_OUTPUT or ENABLE_VIRTUAL_TERMINAL_PROCESSING)
    SetConsoleMode(_coninpfh, ENABLE_VIRTUAL_TERMINAL_INPUT or ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
endif
    _cout(ESC "7" )         ; push cursor
    _cout(CSI "500;500H" )  ; goto x;y (to big)
    _cout(CSI "6n" )        ; read position
    _cursorxy()
    movzx ecx,ax
    shr eax,16
    mov h,eax
    mov w,ecx
    _cout(ESC "8" ) ; pop cursor
    _cout("The size of the console is \e[7m%d:%d\e[0m\n\n", w, h)
   .return(0)

_tmain endp

    end _tstart
