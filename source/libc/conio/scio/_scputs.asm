; _SCPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputs proc x:int_t, y:int_t, string:string_t

    _gotoxy( x, y )
    _cputs( string )
    ret

_scputs endp

    end
