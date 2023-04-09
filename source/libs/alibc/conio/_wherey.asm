; _WHEREY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_wherey proc

    .new x:int_t
    .new y:int_t
    _cout("\e[6n")
    _getcsi2(&x, &y)
    .return( y )

_wherey endp

    end
