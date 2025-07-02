; _TFPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_ftprintf proc uses rbx file:LPFILE, format:tstring_t, argptr:VARARG

    mov  rbx,_stbuf( ldr(file) )
    xchg rbx,_toutput( file, format, &argptr )

    _ftbuf( eax, file )
    .return( rbx )

_ftprintf endp

    end
