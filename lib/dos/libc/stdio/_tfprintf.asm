; _TFPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_ftprintf proc uses bx file:LPFILE, format:LPTSTR, argptr:VARARG

    mov  bx,_stbuf( file )
    xchg bx,_toutput( file, format, &argptr )
    _ftbuf( ax, file )
    .return( bx )

_ftprintf endp

    end
