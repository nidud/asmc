; _TPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_tprintf proc uses rbx format:LPTSTR, argptr:VARARG

    mov ebx,_stbuf( stdout )
    xchg ebx,_toutput( stdout, format, &argptr )
    _ftbuf( eax, stdout )
    mov eax,ebx
    ret

_tprintf endp

    end
