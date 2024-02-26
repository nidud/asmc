; _TFPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_ftprintf proc uses rbx file:LPFILE, format:LPTSTR, argptr:VARARG

    ldr rcx,file
    mov  rbx,_stbuf( rcx )
    xchg rbx,_toutput( file, format, &argptr )

    _ftbuf( eax, file )
    .return( rbx )

_ftprintf endp

    end
