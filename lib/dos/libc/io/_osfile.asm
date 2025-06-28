; _OSFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

.data
 _osfile char_t \
    FOPEN or FDEV or FTEXT,
    FOPEN or FDEV or FTEXT,
    FOPEN or FDEV or FTEXT,
    _NFILE_ - 3 dup(0)

.code

_ioexit proc uses bx

    .for ( bx = 3 : bx < _NFILE_ : bx++ )
        .if ( _osfile[bx] & FOPEN )
            _close( bx )
        .endif
    .endf
    ret

_ioexit endp

.pragma exit(_ioexit, 100)

    end
