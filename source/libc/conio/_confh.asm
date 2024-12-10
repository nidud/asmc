; _CONFH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include conio.inc

    .data
    _confh      HANDLE -1
    _confd      int_t -1
if not defined(__UNIX__) and defined(__TTY__)
    _conoutcp   int_t 0
    _modeout    int_t -1
endif

    .code

__initconout proc private

    mov _confd,_open(CONOUT, O_BINARY or O_RDWR or O_NOCTTY)
    .ifs ( eax > 0 )
        mov _confh,_get_osfhandle(eax)
    .endif
if not defined(__UNIX__) and defined(__TTY__)
    .ifs ( eax > 0 )
        .ifd GetConsoleMode(_confh, &_modeout)
            SetConsoleMode(_confh, ENABLE_PROCESSED_OUTPUT or ENABLE_VIRTUAL_TERMINAL_PROCESSING)
        .endif
    .endif
    mov _conoutcp,GetConsoleOutputCP()
    SetConsoleOutputCP(65001)
endif
    ret

__initconout endp

if not defined(__UNIX__) and defined(__TTY__)
__exitconout proc private

    .if ( _confh > 0 )
        SetConsoleMode(_confh, _modeout)
    .endif
    SetConsoleOutputCP(_conoutcp)
    ret

__exitconout endp

.pragma exit(__exitconout, 10)
endif
.pragma init(__initconout, 21)

    end
