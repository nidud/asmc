; FILE.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.data
 _iob _iobuf \
 { _bufin, 0, _bufin, _IOREAD or _IOYOURBUF, 0, 0, _INTIOBUF },
 { NULL, 0, NULL, _IOWRT, 1, 0, 0 },
 { NULL, 0, NULL, _IOWRT, 2, 0, 0 },
 _NSTREAM_ - 3 dup({ NULL, 0, NULL, 0, -1, 0, 0 })

stdin   LPFILE _iob
stdout  LPFILE _iob[_iobuf]
stderr  LPFILE _iob[_iobuf*2]

.code

__endstdio proc uses si bx

    .for ( bx = 3 : bx < _NSTREAM_ : bx++ )

        imul si,bx,_iobuf
        .if ( _iob[si]._file != -1 )
            fclose( &_iob[si] )
        .endif
    .endf
    ret

__endstdio endp

.pragma exit(__endstdio, 98)

    end
