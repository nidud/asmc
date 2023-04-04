; INITCON.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include fcntl.inc
include conio.inc

    .data
    _confh int_t -2

    .code

__initconout proc

    mov _confh,open("/dev/tty", O_RDWR or O_NOCTTY)
    ret

__initconout endp

__termconout proc

    .if ( _confh > 0 )

	close(_confh)
    .endif
    ret

__termconout endp

.pragma(init(__initconout, 10))
.pragma(exit(__termconout, 20))

    end
