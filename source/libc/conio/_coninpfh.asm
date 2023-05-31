; _CONINPFH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include conio.inc

    .data
ifdef __UNIX__
    told        termios <>
else
    _coninpfh   HANDLE -1
 ifdef __TTY__
    _concp      int_t 0
    _modein     int_t -1
 endif
endif
    _coninpfd   int_t -1

    .code

__initconin proc

    mov _coninpfd,_open(CONIN, O_BINARY or O_RDWR or O_NOCTTY)
ifdef __UNIX__

    .ifsd ( tcgetattr(eax, &told) < 0 )

        .return( 0 )
    .endif

   .new term:termios = told
    and term.c_lflag,not (_ECHO or ICANON)
    or  term.c_iflag,IUTF8
    or  term.c_oflag,OPOST
    or  term.c_lflag,ISIG
    tcsetattr(_coninpfd, TCSANOW, &term)

else

    .ifs ( eax > 0 )
        mov _coninpfh,_get_osfhandle(eax)
    .endif

 ifdef __TTY__

    .ifs ( eax > 0 )
        .ifd GetConsoleMode(_coninpfh, &_modein)
            .ifd SetConsoleMode(_coninpfh,
                    ENABLE_WINDOW_INPUT or ENABLE_VIRTUAL_TERMINAL_INPUT or ENABLE_MOUSE_INPUT)
                FlushConsoleInputBuffer(_coninpfh)
            .endif
        .endif
    .endif
    mov _concp,GetConsoleCP()
    SetConsoleCP(65001)
 endif

endif
    ret

__initconin endp

__exitconin proc

ifdef __UNIX__
    .if ( _coninpfd > 0 )
        tcsetattr(_coninpfd, TCSANOW, &told)
    .endif
else
 ifdef __TTY__
    SetConsoleCP(_concp)
    SetConsoleMode(_coninpfh, _modein)
 endif
endif
    ret

__exitconin endp

.pragma exit(__exitconin, 11)
.pragma init(__initconin, 20)

    end
