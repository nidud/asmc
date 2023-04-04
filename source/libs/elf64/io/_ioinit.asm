; _IOINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include crtl.inc

    .data

    _nfile  dd _NFILE_
    _osfile db FH_OPEN or FH_DEVICE or FH_TEXT
            db FH_OPEN or FH_DEVICE or FH_TEXT
            db FH_OPEN or FH_DEVICE or FH_TEXT
            db _NFILE_ - 3 dup(0)

    .code


_ioexit proc uses rbx r12

    .for ( ebx = 3, r12 = &_osfile : ebx < _NFILE_ : ebx++ )

        .if ( byte ptr [r12+rbx] & FH_OPEN )

            close( ebx )
        .endif
    .endf
    ret

_ioexit endp

.pragma(exit(_ioexit, 100))

    end
