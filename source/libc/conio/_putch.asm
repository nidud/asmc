; _PUTCH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_putch_nolock proc c:int_t

    .if ( _putwch_nolock(wchar_t ptr c) == WEOF )

        mov c,-1
    .endif
    .return( c )

_putch_nolock endp


_putch proc c:int_t

    _putch_nolock( c )
    ret

_putch endp

    end
