; _CONINPFH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include conio.inc

    .data
    _coninpfh   HANDLE -1
    _coninpfd   int_t -1
ifdef __TTY__
 ifdef __UNIX__
    told        termios <>
 else
    _modein     int_t -1
    _concp      int_t 0
 endif
endif

    .code

__initconin proc

    mov _coninpfd,_open(CONIN, O_BINARY or O_RDWR or O_NOCTTY)
    .ifs ( eax > 0 )
        mov _coninpfh,_get_osfhandle(eax)
    .endif

ifdef __TTY__

 ifdef __UNIX__

    .ifsd ( tcgetattr(_coninpfd, &told) < 0 )

        .return( 0 )
    .endif

   .new term:termios = told
    and term.c_lflag,not (_ECHO or ICANON)
    or  term.c_iflag,IUTF8
    or  term.c_oflag,OPOST
    or  term.c_lflag,ISIG
    tcsetattr(_coninpfd, TCSANOW, &term)

 else

    .ifs ( _coninpfd > 0 )
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

ifdef __TTY__

__exitconin proc
ifdef __UNIX__
    .if ( _coninpfd > 0 )
        tcsetattr(_coninpfd, TCSANOW, &told)
    .endif
else
    SetConsoleCP(_concp)
    SetConsoleMode(_coninpfh, _modein)
endif
    ret

__exitconin endp

.pragma exit(__exitconin, 11)
endif
.pragma init(__initconin, 20)

    end
