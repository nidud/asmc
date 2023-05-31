; FPRINTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fprintf proc uses rbx file:LPFILE, format:LPSTR, argptr:VARARG

    mov rbx,_stbuf( file )
    _output( file, format, &argptr )
    xchg rax,rbx
    _ftbuf( eax, file )
    mov rax,rbx
    ret

fprintf endp

    end
