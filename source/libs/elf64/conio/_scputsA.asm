; _SCPUTSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputsA proc uses rbx _x:BYTE, _y:BYTE, string:LPSTR

   .new x:BYTE = _x
   .new y:BYTE = _y
   .new retval:int_t = 0

    .for ( rbx=string : byte ptr [rbx] : rbx++, x++, retval++ )

        _scputc(x, y, 1, [rbx])
    .endf
    .return( retval )

_scputsA endp

    end
