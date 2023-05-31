; FWPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fwprintf proc uses rbx file:LPFILE, format:LPWSTR, argptr:VARARG

    ldr rcx,file
    mov  rbx,_stbuf( rcx )
    xchg rbx,_woutput( file, format, &argptr )

    _ftbuf( eax, file )
    .return( ebx )

fwprintf endp

    end
