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
ifdef __UNIX__
    told        termios <>
endif
    .code

__initconin proc

    mov _coninpfd,_open(CONIN, O_BINARY or O_RDWR or O_NOCTTY)
    .ifs ( eax > 0 )
        mov _coninpfh,_get_osfhandle(eax)
    .endif
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
endif
    ret
    endp

ifdef __UNIX__
__exitconin proc
    .if ( _coninpfd > 0 )
        tcsetattr(_coninpfd, TCSANOW, &told)
    .endif
    ret
    endp

.pragma exit(__exitconin, 11)
endif

.pragma init(__initconin, 20)

    end
