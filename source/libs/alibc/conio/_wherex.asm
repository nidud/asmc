; _WHEREX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_wherex proc

   .new x:int_t
   .new y:int_t
    _cout("\e[6n")
    _getcsi2(&x, &y)
   .return( x )

_wherex endp

    end
