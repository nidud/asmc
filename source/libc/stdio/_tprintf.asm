; _TPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include tchar.inc

    .code

_tprintf proc uses rbx format:tstring_t, argptr:VARARG

    mov ebx,_stbuf( stdout )
    _toutput( stdout, format, &argptr )
    mov ecx,ebx
    mov ebx,eax
    _ftbuf( ecx, stdout )
    mov eax,ebx
    ret

_tprintf endp

    end
