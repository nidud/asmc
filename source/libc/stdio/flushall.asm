; FLUSHALL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

_flushall proc uses rbx

   .new i:int_t = 0
   .new count:int_t = 0

    mov rbx,stdin
    .if ( rbx != NULL )

        .for ( : i < _nstream : i++, rbx+=_iobuf )

            .if ( [rbx]._iobuf._file != -1 )

                fflush(rbx)
                inc count
            .endif
        .endf
    .endif
    .return( count )

_flushall endp

    end
