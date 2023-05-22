; _PUTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include io.inc
include conio.inc

.code

_putch proc c:int_t

    .if ( _conout == -1 )

        mov eax,WEOF
    .else
        ;
        ; write character to console file handle
        ;
        .if ( _write( _conout, &c, 1 ) == 0 )
            mov c,-1
        .endif
    .endif
    .return( c )

_putch endp

    end
