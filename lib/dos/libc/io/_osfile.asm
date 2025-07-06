; _OSFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include dos.inc

define JIT 0x18

.data
 _osfile char_t \
    FOPEN or FDEV or FTEXT,
    FOPEN or FDEV or FTEXT,
    FOPEN or FDEV or FTEXT,
    _NFILE_ - 3 dup(0)

.code

_ioinit proc uses bx di

    .for ( es = _psp, di = JIT+5, bx = 5 : bx < _nfile : bx++, di++ )

        mov _osfile[bx],0
        .if ( byte ptr es:[di] != 0xFF )

            or _osfile[bx],FOPEN or FTEXT
            mov ax,0x4400
            int 0x21
            .if ( !CARRY? && dl & 0x80 )
                or _osfile[bx],FDEV
            .endif
        .endif
    .endf
    ret

_ioinit endp

_ioexit proc uses bx

    .for ( bx = 3 : bx < _nfile : bx++ )
        .if ( _osfile[bx] & FOPEN )
            _close( bx )
        .endif
    .endf
    ret

_ioexit endp

.pragma init(_ioinit, 1)
.pragma exit(_ioexit, 100)

    end
