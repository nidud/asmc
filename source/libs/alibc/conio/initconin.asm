; INITCONIN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include conio.inc
include termios.inc

    .data
    _coninpfh int_t -1
    told termios <>

    .code

__initconin proc

   .new term:termios
    mov _coninpfh,open("/dev/tty", O_RDWR or O_NOCTTY)
    .ifs ( eax > 0 )

	tcgetattr(_coninpfh, &term)
	tcgetattr(_coninpfh, &told)

	and term.c_lflag,not (ICANON or _ECHO)
	mov term.c_cc[VMIN],1
	mov term.c_cc[VTIME],0
	tcsetattr(_coninpfh, TCSANOW, &term)
    .endif
    ret

__initconin endp

__termconin proc

    .if ( _coninpfh > 0 )

	tcsetattr(_coninpfh, TCSANOW, &told)
    .endif
    ret

__termconin endp

.pragma(init(__initconin, 20))
.pragma(exit(__termconin, 20))

    end
