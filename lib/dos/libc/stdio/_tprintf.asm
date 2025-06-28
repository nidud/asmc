; _TPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_tprintf proc uses bx format:LPTSTR, argptr:VARARG

    mov bx,_stbuf( stdout )
    xchg bx,_toutput( stdout, format, &argptr )
    _ftbuf( ax, stdout )
    mov ax,bx
    ret

_tprintf endp

    end
