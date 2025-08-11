; FLUSHALL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

_flushall proc uses rbx

    .if ( stdin != NULL )

        .for ( ebx = 3 : ebx < _nstream : ebx++ )

            imul ecx,ebx,_iobuf
            add rcx,stdin

            .if ( [rcx]._iobuf._file != -1 )
                fclose(rcx)
            .endif
        .endf
    .endif
    ret

_flushall endp

    end
