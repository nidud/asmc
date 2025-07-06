; PRINTF.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

printf proc uses bx format:string_t, argptr:vararg

    mov bx,_stbuf( stdout )
    xchg bx,_output( stdout, format, &argptr )
    _ftbuf( ax, stdout )
    mov ax,bx
    ret

printf endp

    end
