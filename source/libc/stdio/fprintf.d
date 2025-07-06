; FPRINTF.D--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fprintf proc uses bx file:LPFILE, format:string_t, argptr:vararg

    mov  bx,_stbuf( file )
    xchg bx,_output( file, format, &argptr )
    _ftbuf( ax, file )
    .return( bx )

fprintf endp

    end
