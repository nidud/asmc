; _SCPUTSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

    .code

_scputsA proc uses rbx x:BYTE, y:BYTE, string:LPSTR

    .new retval:int_t = 0
     ldr rbx,string
    .for ( : byte ptr [rbx] : rbx++, x++, retval++ )

        movzx ecx,byte ptr [rbx]
        _scputc(x, y, 1, cx)
    .endf
    .return( retval )

_scputsA endp

    end
